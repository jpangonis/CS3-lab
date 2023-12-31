// Julia Pangonis


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using namespace std::placeholders;

struct Peaches {
    double weight; // oz
    bool ripe;  // ripe or not
    void print() const { cout << (ripe ? "ripe" : "green") << ", " << weight << endl; }
};

bool passingWeight(Peaches s, int threshold) {
    return s.weight >= threshold;
}

class isOverJam{
public:
    isOverJam(double JamWeight) : jamWeight_(JamWeight) {}
    bool operator()(Peaches peach) const{
        if (peach.weight < jamWeight_) return true;
        else return false;
    }
private:
    double jamWeight_;
};


int main() {
    srand(time(nullptr));
    const double minWeight = 3.;
    const double maxWeight = 12.;

    cout << "Input basket size: ";
    int size;
    cin >> size;

    vector <Peaches> basket(size);

    // assign random weight and ripeness peaches in the basket
    // replace with generate()
    generate(basket.begin(), basket.end(), [minWeight, maxWeight]() {
        Peaches peach;
        peach.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        peach.ripe = rand() % 2;
        return peach; });

    // for_each() possibly
    cout << "all peaches" << endl;
    for_each(basket.begin(), basket.end(), [](Peaches i) {i.print(); });

    // moving all the ripe peaches from basket to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    deque<Peaches> peck;
    //auto removePredicate = [](const Peaches& peach) { return !peach.ripe; };
    remove_copy_if(basket.begin(), basket.end(), back_inserter(peck), [](const Peaches& peach) { return !peach.ripe; });
    basket.erase(remove_if(basket.begin(), basket.end(),
        [](Peaches peach) {
            return peach.ripe; }),
            basket.end());

    // for_each() possibly
    cout << "peaches remainng in the basket" << endl;
    for_each(basket.begin(), basket.end(), [](Peaches i) {i.print(); });

    cout << endl;

    // for_each() possibly
    cout << "peaches moved to the peck" << endl;
    for (const auto& e : peck) {
        e.print();
    }

    //prints every third peach in the peck
    // prints every "space" peach in the peck
    const int space = 3;
    cout << "\nevery " << space << "\'d peach in the peck" << endl;

    // replace with advance()/next()/distance()
    // no explicit iterator arithmetic

    int step = 2;
    auto it = peck.cbegin();
    while (step < distance(it, peck.cend())) {
        advance(it, step);
        it->print(); 
        step = 3;
    }

    // use a binder to create a functor with configurable max weight
    // accumulate() or count_if() then remove_if()
    const double weightToJam = 10.0;
    double jamWeight = 0;
   
    isOverJam peach1(weightToJam);
    auto isLighterThanJam = std::bind(peach1, _1);

    jamWeight = accumulate(peck.begin(), peck.end(), jamWeight, [&isLighterThanJam](double sum, Peaches peach)
        { if (isLighterThanJam(peach)) return sum + peach.weight; return sum; });

    peck.erase(remove_if(peck.begin(), peck.end(), [&](Peaches peach) { return isLighterThanJam(peach); }), peck.end());

    cout << endl << "Weight of jam is: " << jamWeight << endl;


 }
