// Julia Pangonis

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using std::cout; using std::endl; using std::cin;
using std::vector; using std::string;

class Logger {
public:
    static Logger& instance() {
        static Logger s;
        return s;
    }

    //adding a string to the end of a text file
    void report(const string& add) { fout << add; }

    ~Logger() {
        fout.close();
    }


private:
    // copying prohibited 
    Logger() { 
        fout.open("test.txt", std::fstream::out | std::fstream::app);
    }  

    Logger(const Logger&) {}
    Logger& operator=(const Logger&) {}

    std::ofstream fout;
};

void Func1() {
    string append;
    cout << "What string would you like to add to test.txt: ";
    std::getline(cin, append);
    Logger::instance().report(append);
}

void Func2() {
    Logger::instance().report(" I will pass CS3");
}


// demonstration of singleton usage
int main() {

    Func1();
    Func2();
}