// testing the implementation of class WordList
// Mikhail Nesterenko
// 9/04/2015

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "WordList.hpp"

using std::cout; using std::endl; using std::string; using std::ifstream;

int main(int argc, char* argv[]) {
    //checking the number of arguments listed
    if (argc != 2) {
        cout << "Error: This program requires an argument." << endl;
        return 0;
    }

    WordList words;
    ifstream file(argv[1]);

    string line;
    int startSubstringIndex = 0;
    int counter = 0;

    while (getline(file, line)) {
        for (int i = 0; i < line.length(); ++i) {
            //looping through each character to check if the character is punctuation or a space
            if (!isalnum(line[i]) && line[i] != '\'') {
                string word = line.substr(startSubstringIndex, counter);
                //making sure that there are not multiple punctuations in a row
                if (word.length() > 0) words.addWord(word);

                //finding the next alphanumeric character in order to find where the next word is
                for (int j = i; j < line.length(); ++j) {
                    if (isalnum(line[j])) {
                        startSubstringIndex = j;
                        break;
                    }
                }
                counter = 0;
            }
            else ++counter;
            //checking to see if the last character of the line is a space or punctuation
            if ((i == line.length() - 1) && isalnum(line[i])){
                words.addWord(line.substr(startSubstringIndex, ++counter));
            }
        }
        counter = 0;
        startSubstringIndex = 0;
    }
    cout << "The word list is:\n";
    words.print();

    file.close();

}