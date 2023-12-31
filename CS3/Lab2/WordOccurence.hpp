#ifndef WordOccurence_hpp
#define WordOccurence_hpp

#include <iostream>
#include <string>

using std::string;

class WordOccurrence {
public:
    WordOccurrence(const string& word = "", int num = 0) : word_(word), num_(num) {}; //member initialization list
    bool matchWord(const string&); // returns true if word matches stored
    void increment(); // increments number of occurrences
    string getWord() const;
    int getNum() const;

private:
    string word_;
    int num_;
};

#endif