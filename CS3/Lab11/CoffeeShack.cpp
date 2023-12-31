//Julia Pangonis
/*
#include <string>
#include <iostream>

using std::string; using std::cout; using std::cin; using std::endl;

enum class DrinkType { small, medium, large };

//component
class Drink {
public:
    //setting the originial price of the coffee before add ins
    Drink(DrinkType type = DrinkType::small, int price = 0) :
        type_(type), price_(price) {
        if (type_ == DrinkType::small) price_ = 5;
        else if (type_ == DrinkType::medium) price_ = 7;
        else if (type_ == DrinkType::large) price_ = 10;
    }
    virtual int getPrice() const { return price_; };
    virtual string getName() const {
        string s;
        if (type_ == DrinkType::small) s = "small coffee with ";
        else if (type_ == DrinkType::medium) s = "medium coffee with ";
        else if (type_ == DrinkType::large) s = "large coffee with ";
        return s;
    };
private:
    int price_;
    DrinkType type_;
};

//sugar decorator
class Sugar : public Drink {
public:
    Sugar(Drink* drink) : wrapped_(drink) {}
    int getPrice() const override {return 1 + wrapped_->getPrice();}
    string getName() const override { return wrapped_ ->getName() + "sugar, "; };

private:
    Drink* wrapped_;
};

//cream decorator
class Cream : public Drink {
public:
    Cream(Drink* drink) : wrapped_(drink) {}
    int getPrice() const override {return 2 + wrapped_->getPrice();}
    string getName() const override { return wrapped_->getName() + "cream, "; };

private:
    Drink* wrapped_;
};

//honey decorator
class Honey : public Drink {
public:
    Honey(Drink* drink) : wrapped_(drink) {}
    int getPrice() const override {return 3 + wrapped_->getPrice();}
    string getName() const override { return wrapped_->getName() + "honey, "; };

private:
    Drink* wrapped_;
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
    Drink *finalCoffee = &coffee;
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

    if (count == 0)
        cout << name << " your " << finalCoffee->getName() + "no addins is ready. It will be $" << finalCoffee->getPrice() << " please.";
    else
        cout << name << " your " << finalCoffee->getName().erase(finalCoffee->getName().size()-2) + " is ready. It will be $" << finalCoffee->getPrice() << " please.";
}
*/