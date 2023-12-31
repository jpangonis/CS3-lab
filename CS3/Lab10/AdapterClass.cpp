//Julia Pangonis
// Lab10.cpp

#include <iostream>

using std::cout; using std::endl; using std::cin;

// base interface
class Square {
public:
	virtual void draw() = 0;
	virtual void resize(int) = 0;
	virtual ~Square() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
	LegacyRectangle(int topLeftX,
		int topLeftY,
		int bottomRightX,
		int bottomRightY) :
		topLeftX_(topLeftX),
		topLeftY_(topLeftY),
		bottomRightX_(bottomRightX),
		bottomRightY_(bottomRightY) {}

	void oldDraw() const {
		for (int i = 0; i < bottomRightY_; ++i) {
			for (int j = 0; j < bottomRightX_; ++j)
				if (i >= topLeftY_ && j >= topLeftX_)
					cout << '*';
				else
					cout << ' ';
			cout << endl;
		}
	}

	
	void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
		topLeftX_ = topLeftX;
		topLeftY_ = topLeftY;
		bottomRightX_ = bottomRightX;
		bottomRightY_ = bottomRightY;
	}

	int getTopLeftX() const { return topLeftX_; } 
	int getTopLeftY() const { return topLeftY_; }
	int getBottomRightX() const { return bottomRightX_; } 
	int getBottomRightY() const { return bottomRightY_; }

	// defining top/left and bottom/right coordinates 
private:
	int topLeftX_;
	int topLeftY_;
	int bottomRightX_;
	int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Square,
	private LegacyRectangle {
public:
	SquareAdapter(int size) : LegacyRectangle(0, 0, size, size) {};
	void draw() override {
		oldDraw();
	}

	int size() {
		return getBottomRightX() - getTopLeftX();
	}

	void resize(int newSize) override{
		move(getTopLeftX(), getTopLeftY(), getTopLeftX() + newSize, getTopLeftY() + newSize);
	}
};


int main() {
	int size1;
	cout << "What size would you like the square to be: ";
	cin >> size1;
	Square* square = new SquareAdapter(size1);
	square->draw();

	int size2;
	cout << "What would you like the new size to be: ";
	cin >> size2;

	square->resize(size2);
	square->draw();
}