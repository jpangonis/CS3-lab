//Julia Pangonis

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::make_pair; using std::multimap;


enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

struct Fruit {
    Variety v;
    string color; // red, green or orange
};


int main() {
    srand(time(nullptr));
    //creating a multimap
    multimap<Variety, string> FruitColors;
    auto ranNumFruits = (rand() % 100 + 1);
    
    //random assignment for the variety and color
    for (auto i = 0; i < ranNumFruits; i++) {
        FruitColors.emplace(make_pair(static_cast<Variety>(rand() % 3), colors[rand() % 3]));
    }

    cout << "Colors of the oranges: ";

    //looping through all the fruits and printing out the colors of the just the oranges
    for (auto it = FruitColors.lower_bound(static_cast <Variety>(0)); it != FruitColors.upper_bound(static_cast <Variety>(0)); ++it)
        cout << it->second << endl;

}
