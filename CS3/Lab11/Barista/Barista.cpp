//Julia Pangonis

#include <string>
#include <iostream>
#include "CoffeeShack.hpp"

using std::string;

// abstract class
// sets up individual links in the 
// chain of responsibility
class BaristaTakeOrder {
public:
    BaristaTakeOrder(BaristaTakeOrder* successor = nullptr) :successor_(successor) {}
    virtual void handleRequest(string condition) {
        if (successor_ != nullptr)
            successor_->handleRequest(condition);
        else
            cout << "nobody can handle this request"
            << endl;
    }
private:
    BaristaTakeOrder* successor_;
};

// derived classes
class JuniorBaristaTakeOrder : public BaristaTakeOrder {
public:
    JuniorBaristaTakeOrder(BaristaTakeOrder* successor = nullptr) : BaristaTakeOrder(successor) {}
    void handleRequest(string condition) override {
        if (condition.find("sugar") == string::npos && condition.find("cream") == string::npos && condition.find("honey") == string::npos)
            cout << "The order is being prepared by a Junior Barista" << endl;
        else
            BaristaTakeOrder::handleRequest(condition);
    }
};

// derived classes
class SeniorBaristaTakeOrder : public BaristaTakeOrder {
public:
    SeniorBaristaTakeOrder(BaristaTakeOrder* successor = nullptr) : BaristaTakeOrder(successor) {}
    void handleRequest(string condition) override {
        if ((condition.find("sugar") != string::npos || condition.find("cream") != string::npos) && condition.find("honey") == string::npos)
            cout << "The order is being prepared by a Senior Barista" << endl;
        else
            BaristaTakeOrder::handleRequest(condition);
    }
};

// derived classes
class Manager : public BaristaTakeOrder {
public:
    Manager(BaristaTakeOrder* successor = nullptr) : BaristaTakeOrder(successor) {}
    void handleRequest(string condition) override {
        if (condition.find("honey") != string::npos)
            cout << "The order is being prepared by a Manager" << endl;
        else
            BaristaTakeOrder::handleRequest(condition);
    }
};


int main() {
    char input;
    DrinkType size_;
    cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?";
    cin >> input;
    if (input == 'l') size_ = size_ = DrinkType::large;
    else if (input == 'm') size_ = DrinkType::medium;
    else size_ = DrinkType::small;

    Drink coffee(size_);
    Drink* finalCoffee = &coffee;
    int count = 0;

    cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one?";
    cin >> input;
    while (input != 'd') {
        if (input == 's') {
            finalCoffee = new Sugar(finalCoffee);
            count++;
        }
        else if (input == 'c') {
            finalCoffee = new Cream(finalCoffee);
            count++;
        }
        else if (input == 'h') {
            finalCoffee = new Honey(finalCoffee);
            count++;
        }

        cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one?";
        cin >> input;
    }
    string name;
    cout << "Can I get your name?";
    cin >> name;

    BaristaTakeOrder* tp = new JuniorBaristaTakeOrder(new SeniorBaristaTakeOrder(new Manager)); //calling the constructor in order of responsibility

    tp->handleRequest(finalCoffee->getName()); //respective person handles the drink

    if (count == 0)
        cout << name << " your " << finalCoffee->getName() + "no addins is ready. It will be $" << finalCoffee->getPrice() << " please.";
    else
        cout << name << " your " << finalCoffee->getName().erase(finalCoffee->getName().size() - 2) + " is ready. It will be $" << finalCoffee->getPrice() << " please.";
}
