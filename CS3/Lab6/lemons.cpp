//Julia Pangonis

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::priority_queue;

struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    srand(time(nullptr));
    priority_queue <Lemon> lemons;

    // random quality assingment
    auto boxSize = (rand() % maxBoxSize + 1);
    for (int i = 0; i < boxSize; i++) {
        auto ranQuality = static_cast<double>(rand()) / RAND_MAX * highestQuality;
        Lemon lemon;
        lemon.quality = ranQuality;
        lemons.push(lemon);
    }

    cout << "Here are the lemons (best first): ";
    //returns the best lemon and then removes it from the priority_queue
    while (!lemons.empty()) {
        cout << lemons.top().quality << endl;
        lemons.pop();
    }

}
