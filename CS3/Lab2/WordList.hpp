#ifndef WordList_hpp
#define WordList_hpp

#include <iostream>
#include <string>
#include "WordOccurence.hpp"

using std::string;

//read text file in mainm

class WordList {
public:
    WordList();
    ~WordList();
    WordList& operator=(const WordList&);
    WordList(const WordList&);
    friend bool equal(const WordList&, const WordList&); // implement comparison as friend

    void addWord(const string&);
    void sort();
    void print();
private:
    WordOccurrence* wordArray_; // a dynamically allocated array of WordOccurrences
    int size_;
};

#endif
