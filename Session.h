#pragma once

#include <string>
#include <vector>

namespace WordList {
   std::string_view getRandomWord();
}

class Session
{
public:
	Session();

	std::string_view getWord() const;
	const std::vector<char>& getLetters() const;
	std::vector<char> getWrongGuesses() const;
	std::string getWrongGuessWord() const;
	std::string getGuessedWord() const;

	void setLetter(char symbol, size_t index);
	void setWrongGuessLetter(char l);

	bool isLetterGuessed(char letter) const;

private:
	std::string m_word{};
	std::vector<char> m_letters{};
	std::vector<char> m_wrongGuessses{};
};

