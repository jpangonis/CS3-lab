// Julia Pangonis

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
	Fill(char fillCharBorder,char fillCharInside) : fillCharBorder_(fillCharBorder), fillCharInside_(fillCharInside) {}
	virtual char getBorder() = 0;
	virtual char getInternal() = 0;
	virtual ~Fill() {}
protected:
	char fillCharBorder_;
	char fillCharInside_;
};

// fills the border with the specified char
class Hollow : public Fill {
public:
	Hollow(char fillCharBorder) :Fill(fillCharBorder, ' ') {}
	char getBorder() override { return fillCharBorder_; }
	char getInternal() override { return fillCharInside_ ; }
	~Hollow() override {}
};


// fills the square with the specified char
class Filled : public Fill {
public:
	Filled(char fillCharInside) :Fill(fillCharInside, fillCharInside) {}
	char getBorder() override { return fillCharBorder_; }
	char getInternal() override { return fillCharInside_; }
	~Filled() override {}
};

//fills the outside of the square with the border char
//fills the insude of the square with the internal char
class FullyFilled : public Filled {
public:
	FullyFilled(char fillCharBorder, char fillCharInside) : Filled(fillCharBorder) {fillCharInside_ = fillCharInside;}
};

//randomly fills the square with either the internal or border character
class RandomFilled : public Filled {
public:
	RandomFilled(char fillCharBorder, char fillCharInside) : Filled(fillCharBorder) {fillCharInside_ = fillCharInside;}
	char getBorder() override {return (rand() % 2 == 0) ? fillCharBorder_ : fillCharInside_;}
	char getInternal() override {return (rand() % 2 == 0) ? fillCharBorder_ : fillCharInside_;}
};

// abstract handle
class Figure {
public:
	Figure(int size, Fill* fill) : size_(size), fill_(fill) {}
	virtual void draw() = 0;
	virtual ~Figure() {}
protected:
	int size_;
	Fill* fill_;
};

// concrete handle
class Square : public Figure {
public:
	Square(int size, Fill* fill) : Figure(size, fill) {}
	void draw() override;

};

void Square::draw() {
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j)
			if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
				cout << fill_->getBorder();
			else
				cout << fill_->getInternal();
		cout << endl;
	}
}

int main() {
	srand(time(nullptr));
	
	char borderChar, internalChar;
	int size;
	cout << "Enter border character: ";
	cin >> borderChar;
	cout << "Enter inside character: ";
	cin >> internalChar;
	cout << "Enter size: ";
	cin >> size;

	//calls the new objects for each square
	Figure* hollowSquare = new Square(size,
		new Hollow(borderChar)
	);

	Figure* filledSquare = new Square(size,
		new Filled(internalChar)
	);

	Figure* fullyFilledSquare = new Square(size,
		new FullyFilled(borderChar, internalChar)
	);

	Figure* randomFilledSquare = new Square(size,
		new RandomFilled(borderChar,internalChar)
	);

	//draws each of the squares
	cout << "Hollow Square:" << endl;
	hollowSquare->draw();
	cout << endl;

	cout << "Filled Square:" << endl;
	filledSquare->draw();
	cout << endl;

	cout << "Fully Filled Square:" << endl;
	fullyFilledSquare->draw();
	cout << endl;

	cout << "Randomly Filled Square:" << endl;
	randomFilledSquare->draw();
	cout << endl;

}
