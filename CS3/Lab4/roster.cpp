//Julia Pangonis

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(vector<list<string>>&, string fileName);

// printing a list out
void printRoster(const list<string>&);

//checking if the student name is already in the vector
int check(vector<list<string>>, string, string);

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last"
            << endl;
        exit(1);
    }

    // vector of courses of students
    vector <list<string>> courseStudents;
    //looping through each of the files to find the student name
    for (int i = 1; i < argc - 1; ++i) {
        readRoster(courseStudents, argv[i]);
    }
    cout << "All students:" << endl;
    cout << "first name last name : courses enrolled" << endl;
    for (size_t i = 0; i < courseStudents.size(); ++i) {
        for (string name : courseStudents[i]) {
            cout << name + ' ';
        }
        cout << endl;
    }

    cout << endl;

    // reading in dropouts
    vector <list<string>> dropouts;

    // list of students, removing the dropouts
    list<string> finalList;
    readRoster(dropouts, argv[argc - 1]);

    //looping through the list of students in courses and checking if they
    //are in the dropout vector
    for (size_t i = 0; i < courseStudents.size(); ++i) {
        string first;
        string last;
        int counter = 0;
        for (string name : courseStudents[i]) {
            if (counter == 0) first = name;
            if (counter == 1) last = name;
            counter++;
        }
        string student = "";
        int addElement = check(dropouts, first, last);
        if (addElement < 0) {
            for (string name : courseStudents[i]) {
                student = student + name + ' ';
            }
            finalList.push_back(student);
        }
    }
    cout << "All students,dropouts removed:" << endl;
    cout << "first name last name : courses enrolled" << endl;
    finalList.sort();
    printRoster(finalList);
}
//checking if the name is in the list and returning the position it is in
//returns -1 if it is not in the vector list
int check(vector<list<string>> student, string first, string last) {
    for (size_t i = 0; i < student.size(); ++i) {
        bool checkFirst = false;
        bool checkLast = false;
        int counter = 0;
        for (string name : student[i]) {
            if (counter == 0 && name == first) checkFirst = true;
            if (counter == 1 && name == last) checkLast = true;
            counter++;
        }
        if (checkFirst && checkLast) return i;
    }
    return -1;
}

//reading the roster and adding the names and classes to the vector as a list
void readRoster(vector<list<string>>& student, string fileName) {
    ifstream course(fileName);
    string first, last;
    string newClass = fileName.substr(0, fileName.length() - 4);
    while (course >> first >> last) {
        int vectorPos = -1;
        vectorPos = check(student, first, last);
        if (vectorPos == -1) {
            list<string> classes;
            classes.push_back(first);
            classes.push_back(last);
            classes.push_back(newClass);
            student.push_back(classes);
        }
        else {
            student[vectorPos].push_back(newClass);
        }
    }
    course.close();
}

// printing a list out
void printRoster(const list<string>& roster) {
    for (string name : roster) {
        cout << name << endl;
    }
    cout << endl;
}
