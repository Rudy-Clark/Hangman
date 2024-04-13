// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
// All rights reserver. Author: Rudy Clark

#include "Random.h"
#include "Session.h"

#include <iostream>
#include <limits>

using Index = std::size_t;

void printWord(std::string_view word) {
    std::cout << "The word is: " << word << "\n";
}

void draw(const Session& s) {
    using Index = std::ptrdiff_t;

    std::cout << "The word: ";
    const std::vector<char>& letters{ s.getLetters() };

    for (size_t i{}; i < letters.size(); ++i) {
        if (!letters[i]) {
            std::cout << "_";
        }
        else {
            std::cout << letters[i];
        }
    }
    
    std::cout << "  " << "Wrong guesses: ";
    std::string wrongGuessWord{};
    
    // generate +++ icons 
    for (size_t i{}; i < (6 - s.getWrongGuesses().size()); ++i) {
        std::cout << "+";
    }
    
    wrongGuessWord += s.getWrongGuessWord();

    std::cout << wrongGuessWord << "\n";
}

char getGuessWord(const Session& s) {

    while (true) {
        char letter{};
        std::cout << "Enter your next letter: ";
        std::cin >> letter;

        if (!std::cin) // has a previous extraction failed or overflowed?
        {
            if (std::cin.eof()) // if the stream was closed
            {
                exit(0); // shut down the program now
            }

            std::cin.clear();
            std::cout << "That wasn't a valid input.  Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (letter < 'a' || letter > 'z') {
            std::cout << "That wasn't a valid input.  Try again.\n";
            continue;
        }

        if (s.isLetterGuessed(letter)) {
            std::cout << "You already guessed that.  Try again." << "\n";
            continue;
        }

        return letter;
    }
}

void assignLetter(Session& s, char l) {
    bool found{ false };
    std::string_view word{ s.getWord() };

    for (Index i{}; i < word.length(); ++i) {
        if (word[i] == l) {
            s.setLetter(l, i);
            found = true;
        }
    }

    if (!found) {
        s.setWrongGuessLetter(l);
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)" << "\n";
    std::cout << "To win : guess the word.To lose : run out of pluses." << "\n";

    Session session{};

    std::cout << "DEBUG__";
    printWord(session.getWord());

   
    while(true) {
        
        draw(session);

        char userGues{ getGuessWord(session) };
        assignLetter(session, userGues);
        
        std::cout << "\n";

        if (session.getWrongGuesses().size() == 6) {
            std::cout << "You lost!  The word was: " << session.getWord();
            break;
        }
        else if (session.getGuessedWord() == session.getWord()) {
            std::cout << "You won! The word was: " << session.getWord();
            break;
        }
    }
    
    return 0;
}
