#include <iostream>
#include <string>
#include <fstream>
//g++ lab1.cpp
//./a.out

using std::cout; using std::endl; using std::string; using std::ifstream; using std::ofstream; using std::to_string;

int main(int argc, char* argv[]) {
	//checking to see if there are two arguments
	if (argc != 3) {
		cout << "Error: This program requires two arguments." << endl;
		return 0;
	}

	string nameOfFile1 = argv[1];

	//declaring and opening streams
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);

	string linefile1, linefile2;
	int charDifference = -1;
	int lineCounter = 1;
	string difference;

	//looping through both text files
	while (getline(file2, linefile2) && getline(file1, linefile1)) {
		int minLength;

		//checking if lines are equal
		if (linefile1 != linefile2) {
			if (linefile1.length() < linefile2.length()) {
				minLength = linefile1.length();
			}
			else {
				minLength = linefile2.length();
			}
			//finding the char that is different
			for (int i = 0; i < minLength; i++) {
				if (linefile1[i] != linefile2[i]) {
					charDifference = i;
					break;
				}
			}
			if (charDifference == -1) charDifference = minLength;

			
			cout << argv[1] << ": " << lineCounter << ": " << linefile1 << endl;
			cout << argv[2] << ": " << lineCounter << ": " << linefile2 << endl;

			//find how many characters the line numbers are
			int countDigits = lineCounter;
			int numDigits = 0;
			if (countDigits == 0)
				numDigits = 1;
			while (countDigits != 0) {
				countDigits = countDigits / 10;
				++numDigits;
			}

			//find the length of spaces to add before the caret
			difference = difference.assign(charDifference + 4 + numDigits + nameOfFile1.length(), ' ') + '^';
			cout << difference << endl;
			//closing files and exiting program if difference is found
		}
		lineCounter++;
	}
	file1.close();
	file2.close();

	//reopening files to start reading from the first line
	file1.open(argv[1]);
	file2.open(argv[2]);
	int lineCounterFile1 = 1;
	string line1;
	//if file 1 is longer than file 2, find which line that is
	while (getline(file1, line1)) {
		if (lineCounter == lineCounterFile1) {
			cout << argv[1] << ": " << lineCounter << ": " << line1.substr(0, line1.find_first_of(' ')) << endl;
			cout << argv[2] << ": " << lineCounter << ": " << endl;
			cout << difference.assign(nameOfFile1.length() + 4 + to_string(lineCounter).length(), ' ') << '^' << endl;
		}
		lineCounterFile1++;
	}

	//if file 2 is longer than file 1, find which line that is
	int lineCounterFile2 = 1;
	string line2;
	while (getline(file2, line2)) {
		if (lineCounter == lineCounterFile2) {
			cout << argv[1] << ": " << lineCounter << ": " << endl;
			cout << argv[2] << ": " << lineCounter << ": " << line2.substr(0, line2.find_first_of(' ')) << endl;;
			cout << difference.assign(nameOfFile1.length() + 4 + to_string(lineCounter).length(), ' ') << '^' << endl;
		}
		lineCounterFile2++;
	}

	//closing files and exiting program
	file1.close();
	file2.close();
	return 0;


}