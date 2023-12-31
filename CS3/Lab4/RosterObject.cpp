// Julia Pangonis
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


class Student {
public:
    //default constructor
    Student(string firstName, string lastName) {
        firstName_ = firstName;
        lastName_ = lastName;
    }


    // move constructor, not really needed, generated automatically
    Student(Student&& org) noexcept :
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_)),
        classes(move(org.classes))
    {}

    //accessor for private variables
    string getFirst() { return firstName_; }
    string getLast() { return lastName_; }

    // force generation of default copy constructor
    Student(const Student& org) = default;

    string print() const {
        string courses;
        for (auto student : classes)
            courses = courses + student + ' ';
        return firstName_ + ' ' + lastName_ + ' ' + courses;
    }

    void addItem(string item) { classes.push_back(item); }

    // needed for unique() and for remove()
    friend bool operator== (Student left, Student right) {
        return left.lastName_ == right.lastName_ &&
            left.firstName_ == right.firstName_;
    }

    // needed for sort()
    friend bool operator< (Student left, Student right) {
        return left.lastName_ < right.lastName_ ||
            (left.lastName_ == right.lastName_ &&
                left.firstName_ < right.firstName_);
    }
private:
    string firstName_;
    string lastName_;
    vector<string> classes;
};


// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);
// printing a list out
void printRoster(const list<Student>& roster);
//checking if the student is already in the last
int check(list<Student>, string, string);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    // vector of courses of students
    list<Student> courseStudents;

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(courseStudents, argv[i]);
    }
    cout << "All students: " << endl;
    printRoster(courseStudents);


    // reading in dropouts
    list<Student> dropouts;
    readRoster(dropouts, argv[argc - 1]);
    cout << "\n\n dropouts \n"; printRoster(dropouts);

    list<Student> allStudents;// master list of students
    allStudents = move(courseStudents);

    cout << "\n\n all students sorted, dropouts removed \n";
    for (const auto& str : dropouts)  // removing individual dropouts
        allStudents.remove(str);
    allStudents.sort(); //sorting all students on last name
    printRoster(allStudents);

}

//checking if the student is in the list
//returns 1 if it is, returns -1 if not
int check(list<Student> student, string first, string last) {
    bool checkFirst = false;
    bool checkLast = false;
    for (Student name : student) {
        if (name.getFirst() == first) checkFirst = true;
        if (name.getLast() == last) checkLast = true;
    }
    if (checkFirst && checkLast) return 1;
    return -1;
}

//reads the list of names, adds new student if they aren't in the list
//adds class if student is already in list
void readRoster(list<Student>& classes, string fileName) {
    ifstream course(fileName);
    string first, last;
    string newClass = fileName.substr(0, fileName.length() - 4);
    while (course >> first >> last) {
        int vectorPos = -1;
        vectorPos = check(classes, first, last);
        if (vectorPos == -1) {
            classes.push_back(Student(first, last));

        }
        for (auto& name : classes) {
            if (name.getFirst() == first && name.getLast() == last) {
                name.addItem(newClass);
            }
        }
    }
    course.close();
}

// printing a list out
void printRoster(const list<Student>& roster) {
    for (const auto& student : roster)
        cout << student.print() << endl;
}
