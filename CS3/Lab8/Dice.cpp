// Julia Pangonis

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl; using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
    Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

    // template method
    void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_ = 0;

        initializeGame();

        for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
            makeMove(i);
            if (i == playersCount_ - 1)
                ++movesCount_;
        }
        printWinner();
    }

    virtual ~Game() {}

protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual void printWinner() = 0;
    virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
    // returns true if winner is decided
    static const int noWinner = -1;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
    // implementing concrete methods
    void initializeGame() {
        playersCount_ = rand() % numPlayers_ + 1; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Monopoly, player " << playerWon_ << " won in "
            << movesCount_ << " moves." << endl;
    }

private:
    static const int numPlayers_ = 8; // max number of players
    static const int minMoves_ = 20; // nobody wins before minMoves_
    static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game {
public:
    void initializeGame() {
        playersCount_ = numPlayers_; // initalize players
        for (int i = 0; i < numPlayers_; ++i)
            experience_[i] = rand() % maxExperience_ + 1;
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = (rand() % maxMoves_) / experience_[player];
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Chess, player " << playerWon_
            << " with experience " << experience_[playerWon_]
            << " won in " << movesCount_ << " moves over"
            << " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
            << endl;
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 2; // nobody wins before minMoves_
    static const int maxMoves_ = 100; // somebody wins before maxMoves_
    static const int maxExperience_ = 5; // player's experience
    // the higher, the greater probability of winning
    int experience_[numPlayers_];
};

class Dice : public Game {
public:
    void initializeGame() {
        playersCount_ = 2;
        roundNumber = 1;
        rollAgain = 'y';
        ComputerRollAgain = 1;
        for (int i = 0; i < 6; i++) {
            computerRolls[i] = 0;
            humanRolls[i] = 0;
        }
    }

    void makeMove(int player) {
        int computerSum;
        int humanSum;

        while (roundNumber < rolls) {
            //rolling for when the computer and human have not passed
            if (rollAgain == 'y' && ComputerRollAgain == 1) {
                computerSum = rollComputer();
                humanSum = rollHuman();
                cin >> rollAgain;
                ComputerRollAgain = rand() % 2;
                roundNumber++;
            }
            //rolling if the computer has passed but not the human
            else if (rollAgain == 'y' && ComputerRollAgain == 0) {
                cout << "Round " << roundNumber << ": Computer rolled: passed , computer's score = " << computerSum << endl;
                humanSum = rollHuman();
                cin >> rollAgain;
                roundNumber++;
            }
            //rolling if the human has passed but not the computer 
            else if (rollAgain == 'n' && ComputerRollAgain == 1) {
                computerSum = rollComputer();
                cout << "You rolled: passed, your score = " << humanSum << endl;
                cout << "Roll again? [y/n] ";
                cin >> rollAgain;
                roundNumber++;
            }
            else roundNumber++;

        }
        //finding out the winner based on who has the higher score
        if (computerSum >= humanSum) playerWon_ = 0;
        else if (computerSum < humanSum) playerWon_ = 1;
    }

    int rollHuman() {
        int humanSum = 0;
        cout << "You rolled: ";
        for (int i = 0; i < 6; i++) {
            humanRolls[i] = rand() % 6 + 1;
            humanSum += humanRolls[i];
            cout << humanRolls[i] << ' ';
        }
        cout << ", your score = " << humanSum << endl;
        cout << "Roll again? [y/n] ";
        return humanSum;
    }

    int rollComputer() {
        int computerSum = 0;
        cout << "Round " << roundNumber << ": Computer rolled: ";
        for (int i = 0; i < 6; i++) {
            computerRolls[i] = rand() % 6 + 1;
            computerSum += computerRolls[i];
            cout << computerRolls[i] << ' ';
        }
        cout << ", computer's score = " << computerSum << endl;
        return computerSum;

    }

    void printWinner() {
        if (playerWon_ == 0) cout << "You lose!";
        else if (playerWon_ == 1) cout << "You win!";
    }

private:
    static const int rolls = 3;
    int roundNumber;
    char rollAgain;
    bool ComputerRollAgain;
    int computerRolls[6];
    int humanRolls[6];
};

int main() {
    srand(time(nullptr));

    Game* gp = nullptr;

    /*
    // play chess 8 times
    for (int i = 0; i < 8; ++i) {
        gp = new Chess;
        gp->playGame();
        delete gp;
    }


    // play monopoly 8 times
    for (int i = 0; i < 8; ++i) {
        gp = new Monopoly;
        gp->playGame();
        delete gp;
    }
    */
    //play the Dice game once
    gp = new Dice;
    gp->playGame();
    delete gp;
}
