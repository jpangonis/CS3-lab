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
    int getPrice() const override { return 1 + wrapped_->getPrice(); }
    string getName() const override { return wrapped_->getName() + "sugar, "; };

private:
    Drink* wrapped_;
};

//cream decorator
class Cream : public Drink {
public:
    Cream(Drink* drink) : wrapped_(drink) {}
    int getPrice() const override { return 2 + wrapped_->getPrice(); }
    string getName() const override { return wrapped_->getName() + "cream, "; };

private:
    Drink* wrapped_;
};

//honey decorator
class Honey : public Drink {
public:
    Honey(Drink* drink) : wrapped_(drink) {}
    int getPrice() const override { return 3 + wrapped_->getPrice(); }
    string getName() const override { return wrapped_->getName() + "honey, "; };

private:
    Drink* wrapped_;
};