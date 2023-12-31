// Julia Pangonis

#include <fstream>
#include <iostream>
#include <set>
#include <string>

using std::ifstream;
using std::string; using std::getline;
using std::cout; using std::endl;
using std::set;


class Student {
public:
    Student(string firstName, string lastName) :
        firstName_(firstName), lastName_(lastName) {}

    // move constructor, not really needed, generated automatically
    Student(Student&& org) noexcept :
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_))
    {}

    // force generation of default copy constructor
    Student(const Student& org) = default;

    string print() const { return firstName_ + ' ' + lastName_; }

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
};


// reading a list from a fileName
void readRoster(set<Student>& roster, string fileName);
// printing a list out
void printRoster(const set<Student>& roster);
//removes dropouts from set
void removeDropouts(set<Student>& roster, string fileName);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    //set of students enrolled
    set<Student> courseStudents;

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(courseStudents, argv[i]);
    }
    cout << "All students: " << endl;
    printRoster(courseStudents);

    //remove dropouts from list of students
    removeDropouts(courseStudents, argv[argc - 1]);

    cout << endl << "All students, droupouts removed" << endl;
    printRoster(courseStudents);

}

//reads the list of names, adds new student 
//when inserting sets do not add duplicates so do not need to check
void readRoster(set<Student>& classes, string fileName) {
    ifstream course(fileName);
    string first, last;
    string newClass = fileName.substr(0, fileName.length() - 4);
    while (course >> first >> last) {
        classes.insert(Student(first, last));
    }

    course.close();
}

//reads the dropouts file and erases all students that have a name
//in the dropout list
void removeDropouts(set<Student>& roster, string fileName) {
    ifstream course(fileName);
    string first, last;
    while (course >> first >> last) {
        auto removeStudent = Student(first, last);
        roster.erase(removeStudent);
    }
}

// printing a list out
void printRoster(const set<Student>& roster) {
    for (const auto& student : roster) {
        cout << student.print() << endl;
    }
}
