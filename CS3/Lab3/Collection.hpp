//list.hpp is a private member of this class
// need a pointer to the first element in the list
#include <iostream>
#include <string>
#include "list.hpp"

using std::cout; using std::endl;

template<typename T>
class Collection;


// forward function declaration
template<typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
	Collection(); //cponstructor
	void add(T); //adds an item to the front of the collection
	void remove(T); //removes the item in the parameter from the collection
	T last(); //return the last item in the collection
	void print();  //prints the collection

	// this is a friend to only a single instance
	// note the angle brakets: tells compiler it is a template
	friend bool equal<T>(const Collection&, const Collection&);
private:
	node<T>* head; //front of the collection
	int size_; //size of the collection
};

//constructor
template <typename T>
Collection<T>::Collection() {
	int size_ = 0;
	head = new node<T>;
}

//adds item to the front of the collection
template <typename T>
void Collection<T>::add(T item) {
	++size_;
	if (size_ <= 1)
	head->setData(item);
	else {
		node<T>* current1 = head;
		while (current1) {
			if (current1->getNext() == nullptr) {
				node<T>* const newNode = new node<T>;
				newNode->setData(item);
				current1->setNext(newNode);
				break;
			}
			else {
				current1 = current1->getNext();
			}
		}
	}
	
}

//removes the item from teh collection
template <typename T>
void Collection<T>::remove(T item) {
	node<T>* current1 = head;
	node<T>* previous = nullptr;

	while (current1) {
		//checking if this element in list is the item
		if (current1->getData() == item) {
			//if the item is the head
			if (previous == nullptr) {
				head = current1->getNext();
				delete current1;
				current1 = head;
			}
			//if item is not the head
			else {
				previous->setNext(current1->getNext());
				delete current1;
				current1 = previous;
			}
		}
		//if not the item, then go to next item
		else {
			previous = current1;
			current1 = current1->getNext();
		}
	}
}

// returns the last element in the collection
template <typename T>
T Collection<T>::last() {
	node<T>* last = nullptr;
	for (node<T>* current = head; current != nullptr; current = current->getNext()) {
		if (current->getNext() == nullptr) {
			last = current;
		}
	}
	return last->getData();
}

//prints the collection
template <typename T>
void Collection<T>::print() {
	for (node<T>* current = head; current != nullptr; current = current->getNext())
		cout << current->getData() << ' ';
	cout << endl;

}

//friend function to check if each item in the collection is the same
template <typename T>
bool equal(const Collection<T>& x, const Collection<T>& y) {
	node<T>* current1 = x.head;
	node<T>* current2 = y.head;

	while (current1 != nullptr && current2 != nullptr) {
		if (current1->getData() != current2->getData()) {
			return false; 
		}
		current1 = current1->getNext();
		current2 = current2->getNext();
	}

	//checks if collections are the same size
	if (current1 != nullptr || current2 != nullptr) {
		return false;
	}

	return true;
}
