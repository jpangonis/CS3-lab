//Julia Pangonis

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout; using std::endl;
using std::map; using std::set;
using std::string;

class Observer;
class Subject;

class EventRegistry {
public:
    static void registerObserver(const string subjectName, Observer*);
    static void deregisterObserver(const string subjectName, Observer*);
    static void handleMessage(const string subjectName);
private:
    static map<string, set<Observer*>> observerMap_;
};

// initialize the static map
map<string, set<Observer*>> EventRegistry::observerMap_;

class Observer {
public:
    Observer(const string name) : name_(name) {}
    string getName() const { return name_; }
    void subscribe(const string subjectName) { EventRegistry::registerObserver(subjectName, this); }
    void unsubscribe(const string subjectName) { EventRegistry::deregisterObserver(subjectName, this); }
    void handleMessage(const string subjectName);
private:
    string name_;
};

class Subject {
public:
    Subject(const string name) : name_(name) {}
    string getName() const { return name_; }
    void generateMessage() {
        cout << name_ << " sent a message" << endl;
        EventRegistry::handleMessage(name_);
    }
private:
    string name_;
};

void EventRegistry::registerObserver(const string subjectName, Observer* o) {
    observerMap_[subjectName].insert(o);
    cout << o->getName() << " subscribed to " << subjectName << endl;
}

void EventRegistry::deregisterObserver(const string subjectName, Observer* o) {
    observerMap_[subjectName].erase(o);
    cout << o->getName() << " unsubscribed from " << subjectName << endl;
}

void EventRegistry::handleMessage(const string subjectName) {
    for (auto e : observerMap_[subjectName])
        e->handleMessage(subjectName);
}

void Observer::handleMessage(const string subjectName) {
    cout << name_ << " received message from " << subjectName << endl;
}

int main() {
    Subject sue("Subject Sue"), steve("Subject Steve");
    Observer olaf("Observer Olaf"), olga("Observer Olga");

    olaf.subscribe(sue.getName());
    olaf.subscribe(steve.getName());
    olga.subscribe(sue.getName());

    cout << endl;

    sue.generateMessage();
    steve.generateMessage();
    cout << endl;

    olga.unsubscribe(sue.getName());
    sue.generateMessage();
}
