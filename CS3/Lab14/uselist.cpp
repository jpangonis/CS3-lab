#include <iostream>
#include <memory>
#include "list.hpp" 

using std::cout;
using std::endl;
using std::weak_ptr; 
using std::shared_ptr;
using std::make_shared;

int main() {
    shared_ptr<node<int>> head, currentPtr;

    // integer list manipulation

    // first node
    head = std::make_shared<node<int>>(1);

    currentPtr = make_shared<node<int>>(2);  // second node
    head->setNext(currentPtr); 
    currentPtr->setPrev(head);

    cout << head->getData() << " "; // printing head node

    // printing and deallocating the last element
    cout << head->getNext()->getData() << endl;

    // character list manipulation

    // allocating head node
    auto charHead = make_shared<node<char>>('A');
    auto charCurrent = charHead;

    // creating list
    for (char letter = 'B'; letter <= 'Z'; ++letter) {
        auto newNode = make_shared<node<char>>(letter);
        newNode->setPrev(charCurrent);
        charCurrent->setNext(newNode);
        charCurrent = newNode;
    }

    // printing characters using shared_ptr
    for (charCurrent = charHead; charCurrent != nullptr; charCurrent = charCurrent->getNext()) {
        cout << charCurrent->getData() << ' ';
    }
    cout << endl;

    return 0;
}
