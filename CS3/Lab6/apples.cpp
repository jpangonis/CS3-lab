// Julia Pangonis


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string; using std::generate;
using std::vector; using std::deque;

struct Apples {
    double weight; // oz
    string color;  // red or green
    void print() const { cout << color << ", " << weight << endl; }
};



int main() {
    srand(time(nullptr));
    const double minWeight = 3.;
    const double maxWeight = 8.;

    cout << "Input crate size: ";
    int size;
    cin >> size;

    vector <Apples> crate(size);

    // assign random weight and color to apples in the crate
    // replace with generate()
    generate(crate.begin(), crate.end(), [minWeight, maxWeight]() {
        Apples apple;
        apple.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        apple.color = rand() % 2 == 1 ? "green" : "red";
    return apple; });


    // for_each() to print out all the apples
    cout << "all apples" << endl;
    for_each(crate.begin(), crate.end(), [](Apples i) {i.print(); });
    
    cout << "Enter weight to find: ";
    double toFind;
    cin >> toFind;

    //find how many apples are heavier than the weight to find
    // count_if()
    int count = count_if(crate.begin(), crate.end(), [&](Apples i) {return i.weight > toFind; });
  
    cout << "There are " << count << " apples heavier than "
        << toFind << " oz" << endl;

    //find the positions of the apples heavier than the weight to find
    //find_if()
    auto it=find_if(crate.begin(), crate.end(),[toFind](Apples apple){return apple.weight > toFind;});

    if (it != crate.end()) {
        cout << "at position(s): ";
        do {
            cout << it - crate.begin() << " ";
            it = find_if(it+1, crate.end(), [toFind](Apples apple) {return apple.weight > toFind; });
        } while (it != crate.end());
    }

    //find the heaviest apple
    // max_element()
    auto heaviest = max_element(crate.begin(), crate.end(), [](Apples a, Apples b) {return a.weight < b.weight; });
    cout << "Heaviest apple weighs: "<< heaviest->weight  << " oz" << endl;

    //find the weight of all the apples combines
    // accumulate()
    double sum = accumulate(crate.begin(), crate.end(), 0.0,[](double sum, const Apples& apple) {return apple.weight + sum;});
    cout << "Total apple weight is: " << sum << " oz" << endl;


    //grow the apples a given amount
    // transform();
    cout << "How much should they grow: ";
    double toGrow;
    cin >> toGrow;
    transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples apple) {Apples appleGrowed;  
    appleGrowed.weight = apple.weight + toGrow; appleGrowed.color = apple.color;
    return appleGrowed; });

    //remove apple if it is less than the minimum weight
    // remove_if()
    cout << "Input minimum acceptable weight: ";
    double minAccept;
    cin >> minAccept;

    crate.erase(remove_if(crate.begin(), crate.end(),
        [minAccept](Apples apple) {
            return apple.weight < minAccept; }) ,
        crate.end());

    cout << "removed " << size - crate.size() << " elements" << endl;

    //sort the apples based on weight
    //sort()
    sort(crate.begin(), crate.end(), [](Apples a, Apples b) {return a.weight < b.weight; });


    // for_each() to print all the remaining apples
    cout << "sorted remaining apples" << endl;
    for_each(crate.begin(), crate.end(), [](Apples i) {i.print(); });

}
