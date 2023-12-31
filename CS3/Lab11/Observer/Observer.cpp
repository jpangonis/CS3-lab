#include <string>
#include <iostream>
#include <vector>
#include "CoffeeShack.hpp"
#include "Barista.hpp"

using std::string; using std::cout; using std::cin; using std::endl;
using std::vector;


// Forward declarations
class Customer;

//enum class DrinkType { small, medium, large };

class Barista {
public:
    void registerCustomer(Customer* customer);
    void allDrinksReady();
    void notifyCustomers();

private:
    vector<Customer*> customers_;
};

class Customer {
public:
    Customer(const string name, Barista* barista, Drink* drink, int price, string CoffeeName);
    void orderDrink();
    void notifyDrinkReady();
    int getPrice() const { return price_; };
    string getCoffeeName() const { return CoffeeName_; };

private:
    string name_;
    Barista* barista_;
    Drink* drink_;
    int price_;
    string CoffeeName_;
};


void Barista::registerCustomer(Customer* customer) {
    customers_.push_back(customer);
}

void Barista::notifyCustomers() {
    if (customers_.empty()) {
        return;
    }
    int randomIndex = rand() % customers_.size();
    Customer* selectedDrink = customers_[randomIndex];
    selectedDrink->notifyDrinkReady();

    customers_.erase(customers_.begin() + randomIndex);
}

void Barista::allDrinksReady() {
    for (Customer* c : customers_)
    {
        c->notifyDrinkReady();
    }
    customers_.clear();
}

Customer::Customer(const string name, Barista* barista, Drink* drink, int price, string CoffeeName) : name_(name), barista_(barista), drink_(drink), price_(price), CoffeeName_(CoffeeName) {
    barista_->registerCustomer(this);
}

void Customer::orderDrink() {
    if (getCoffeeName().find("sugar") == string::npos && getCoffeeName().find("cream") == string::npos && getCoffeeName().find("honey") == string::npos)
        cout << name_ << " your " << getCoffeeName() + "no addins order has been placed.";
    else
        cout << name_ << " your " << getCoffeeName().erase(getCoffeeName().size() - 2) + " order has been placed. ";
    BaristaTakeOrder* tp = new JuniorBaristaTakeOrder(new SeniorBaristaTakeOrder(new Manager)); //calling the constructor in order of responsibility

    tp->handleRequest(getCoffeeName());
}

void Customer::notifyDrinkReady() {
    if (getCoffeeName().find("sugar") == string::npos && getCoffeeName().find("cream") == string::npos && getCoffeeName().find("honey") == string::npos)
        cout << name_ << " your " << getCoffeeName() + "no addins is ready." << endl;
    else
        cout << name_ << " your " << getCoffeeName().erase(getCoffeeName().size() - 2) + " is ready." << endl;
}


void newCustomer(Barista& barista) {
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

    Customer* customer1 = new Customer(name, &barista, finalCoffee, finalCoffee->getPrice(), finalCoffee->getName());
    customer1->orderDrink();
}

int main() {
    srand(time(nullptr));
    int count = 0;
    Barista b;
    newCustomer(b);
    count++;
    while (count < 4) {
        int num = rand() % 2;
        if (num == 0) {
            newCustomer(b);
            count++;
        }
        else {
            b.notifyCustomers();
        }
    }
    b.allDrinksReady();
}


