#include <iostream>
#include "WordList.hpp"

using std::cout; using std::endl; using std::swap;

//initializes the private variables
WordList::WordList() {
	size_ = 0;
	wordArray_ = new WordOccurrence[size_];
}

//copy constructor
WordList::WordList(const WordList& org) {
	size_ = org.size_;
	wordArray_ = new WordOccurrence[size_];
	for (int i = 0; i < size_; ++i)
		wordArray_[i] = org.wordArray_[i];
}

//overloading the equals sign
WordList& WordList::operator=(const WordList& rhs) {
	if (this != &rhs) { // if not same
		size_ = rhs.size_;
		delete[] wordArray_;
		wordArray_ = new WordOccurrence[size_];
		for (int i = 0; i < size_; ++i)
			wordArray_[i] = rhs.wordArray_[i];
	}
	return *this;
}

//friend function to check if two objects are equal to each other
bool equal(const WordList& left, const WordList& right) {
	if (left.size_ != right.size_) return false;
	else {
		for (int i = 0; i < left.size_; ++i) {
			if ((left.wordArray_[i].getWord() == right.wordArray_[i].getWord()) && (left.wordArray_[i].getNum() == right.wordArray_[i].getNum())) {
				return true;
			}
			else return false;
		}
	}
}

//adds word to the WordOccurence array (wordArray_)
//uses the matchWord function to increment the number of occurrences and check if the word already exists
//initializes a temporary array in order to increase the size
void WordList::addWord(const string& newWord) {
	bool inArray = false;
	for (int i = 0; i < size_; ++i) {
		if (wordArray_[i].getWord() == newWord) {
			inArray = wordArray_[i].matchWord(newWord);
		}
	}

	if (!inArray) {
		++size_;
		WordOccurrence* newArr = new WordOccurrence[size_];
		for (int i = 0; i < size_ - 1; ++i) {
			newArr[i] = wordArray_[i];
		}
		delete[] wordArray_;
		wordArray_ = newArr;
		wordArray_[size_ - 1] = WordOccurrence(newWord, 1);
	}
}

//sorts the array before it is printed so that rarest words are printed first
void WordList::sort() {
	int min;

	for (int i = 0; i < size_ - 1; i++) {
		min = i;
		for (int j = i + 1; j < size_; j++) {
			if (wordArray_[j].getNum() < wordArray_[min].getNum())
				min = j;
		}

		if (min != i) {
			//WordOccurrence temp = wordArray_[min];
			//wordArray_[min] = wordArray_[i];
			//wordArray_[i] = temp;

			swap(wordArray_[min], wordArray_[i]);
		}
			
	}
}

//prints the sorted array and outputs the words and numbers in a way that is easy to read
void WordList::print() {
	sort();
	cout << "Word:   Count:" << endl; 
	for (int i = 0; i < size_; ++i) {
		if (wordArray_[i].getWord().length() <= 8) {
			string output(8 - wordArray_[i].getWord().length(), ' ');
			cout << wordArray_[i].getWord() << output << wordArray_[i].getNum() << endl;
		}
		else {
			string output = " ";
			cout << wordArray_[i].getWord() << output << wordArray_[i].getNum() << endl;
		}
		
	}
}

//destructor
WordList::~WordList() {
	delete[] wordArray_;
}
