// Julia Pangonis

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl; using std::string;

class CarLot {
public:
    CarLot();
    
    // if a car is bought, requests a new one
    Car* buyCar(int i) {
        Car* bought = car4sale_;
        carLot_[i] = factories_[rand() % factories_.size()]->requestCar();
        return bought;
    }

    //customer drives the next car in the lost
    Car* nextCar() {
        Car* nextCar_ = carLot_[currentCar];
        if (currentCar == 7) currentCar = 0;
        else currentCar++;
        return nextCar_;
    }

    //number of cars allowed in the lot
    int lotSize() { return lotSize_; }

private:
    Car* car4sale_; // single car for sale at the lot
    vector<CarFactory*> factories_;
    int const lotSize_ = 8;
    vector<Car*> carLot_; //random vector of cars in the lot
    int currentCar = 0; //used to increment for next car
};


CarLot::CarLot() {
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    // randomly populates the vectors of cars in the lot
    for (int i = 0; i < lotSize(); i++)
        carLot_.push_back(factories_[rand() % factories_.size()]->requestCar());
    
}

CarLot* carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();

    //assigns a random model that the customer wants
    Toyota* Toyotacar = new Toyota();
    string Toyotamodel = Toyotacar->getModel();

    for (int i = 0; i < carLotPtr->lotSize(); i++) {
        Car* toBuy = carLotPtr->nextCar();

        cout << "Jill Toyoter " << id << endl;
        cout << "test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel();

        if (toBuy->getMake() == "Toyota" && toBuy->getModel() == Toyotamodel) {
            cout << " love it! buying it!" << endl;
            carLotPtr->buyCar(i);
            break;
        }
        else
            cout << " did not like it!" << endl;
    }
}

// test-drives a car
// buys it if Ford
void fordLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();

    //assigns a random model that the customer wants
    Ford* Fordcar = new Ford();
    string Fordmodel = Fordcar->getModel();

    for (int i = 0; i < carLotPtr->lotSize(); i++) {
        Car* toBuy = carLotPtr->nextCar();

        cout << "Jack Fordman " << id << endl;
        cout << "test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel();

        if (toBuy->getMake() == "Ford" && toBuy->getModel() == Fordmodel) {
            cout << " love it! buying it!" << endl;
            carLotPtr->buyCar(i);
            break;
        }
        else
            cout << " did not like it!" << endl;
    }
}



int main() {
    srand(time(nullptr));

    const int numBuyers = 10;
    for (int i = 0; i < numBuyers; ++i) {
        if (rand() % 2 == 0) {
            toyotaLover(i);
            cout << "+++++++++++++++++" << endl;
        }
        else {
            fordLover(i);
            cout << "+++++++++++++++++" << endl;
        }

    }
}