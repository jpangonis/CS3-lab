#include <string>
#include <iostream>

using std::string; using std::cout; using std::cin; using std::endl;

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