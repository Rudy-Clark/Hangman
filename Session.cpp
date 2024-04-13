#include "Session.h"
#include "Random.h"

#include <iostream>

namespace WordList {
	using namespace std::string_literals;
	// list random words
	const std::vector<std::string_view> words{ "mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

	std::string_view getRandomWord () {
		int randomRange = Random::get(0, words.size() - 1);
		return words[randomRange];
	}
}

Session::Session() {
	m_word = WordList::getRandomWord();
	m_letters = std::vector<char>(m_word.length());
	m_wrongGuessses = std::vector<char>(0);
}

std::string_view Session::getWord() const {
	return m_word;
}

const std::vector<char>& Session::getLetters() const
{
	return m_letters;
}

void Session::setLetter(char symbol, std::size_t index)
{
	m_letters[index] = symbol;
}

bool Session::isLetterGuessed(char letter) const
{
	bool bResult{ false };
	for (size_t i{}; i < m_letters.size(); ++i) {
		if (m_letters[i] == letter) {
			bResult = true;
		}
	}

	return bResult;
}

std::vector<char> Session::getWrongGuesses() const
{
	return m_wrongGuessses;
}

void Session::setWrongGuessLetter(char l)
{
	m_wrongGuessses.push_back(l);
}

std::string Session::getWrongGuessWord() const
{
	std::string result{};

	for (std::size_t i{}; i < m_wrongGuessses.size(); ++i) {
		result += m_wrongGuessses[i];
	}

	return result;
}

std::string Session::getGuessedWord() const
{
	std::string guessWord{};

	for (size_t i{}; i < m_letters.size(); ++i) {
		guessWord += m_letters[i];
	}

	return guessWord;

}


