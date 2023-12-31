// Julia Pangonis

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::make_pair;
using std::cout; using std::endl;
using std::map;


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
void readRoster(map<Student, list<string>>& roster, string fileName);
// printing a map out
void printRoster(const map<Student, list<string>>& roster);
//remove students that have name in dropout list
void removeDropouts(map<Student, list<string>>& roster, string fileName);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    //map of courses of students
    map<Student, list<string>> courseStudents;

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(courseStudents, argv[i]);
    }
    cout << "All students: " << endl;
    printRoster(courseStudents);

    removeDropouts(courseStudents, argv[argc - 1]);

    cout << endl << "All students, droupouts removed" << endl;
    printRoster(courseStudents);

}

//reads the list of names, adds new student if they aren't in the map already
//if they are in the map then just the new class is added
void readRoster(map<Student, list<string>>& student, string fileName) {
    ifstream course(fileName);
    string first, last;
    string newClass = fileName.substr(0, fileName.length() - 4);
    while (course >> first >> last) {
        list<string> classes;
        classes.push_back(newClass);
        auto findStudent = Student(first, last);
        auto it = student.find(findStudent);
        if (it != student.end()) student[findStudent].push_back(newClass);
        else student.insert(make_pair(findStudent, classes));

    }

    course.close();
}

//reads dropout list and removes all students from the final list that are 
//in the dropout list
void removeDropouts(map<Student, list<string>>& roster, string fileName) {
    ifstream course(fileName);
    string first, last;
    while (course >> first >> last) {
        auto eraseStudent = Student(first, last);
        roster.erase(eraseStudent);
    }
}

// printing a map out
void printRoster(const map<Student, list<string>>& roster) {
    for (const auto& student : roster) {
        cout << student.first.print() << ' ';
        for (const auto& cla : student.second)
            cout << cla << ' ';
        cout << endl;
    }
}

