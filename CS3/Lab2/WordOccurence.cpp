#include "WordOccurence.hpp"
#include <iostream>

//returns true if the word matches the stored word, increments the num if it does match
bool WordOccurrence::matchWord(const string& newWord) {
	if (newWord == word_) {
		increment();
		return true;
	}
	else return false;
}

void WordOccurrence::increment() {
	num_++;
}

string WordOccurrence::getWord() const{
	return word_;
}

int WordOccurrence::getNum() const {
	return num_;
}