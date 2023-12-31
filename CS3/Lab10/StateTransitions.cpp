// Julia Pangonis

#include <iostream>
#include <string>
using std::cin; using std::cout; using std::endl; using std::string;
using std::to_string;

class State;

// context
class Process {
public:
    Process(State* prototype);

    // behaviors
    void Dispatch();
    void Suspend();
    void Block();
    void unBlock();
    int exit();
    string report();

    static int getNextProcessID() {
        return nextProcessID_++;
    }

    // part of implementation of state pattern
    void changeState(State* state) { state_ = state; }
private:
    State* state_;
    int processID_;
    static int nextProcessID_;
};

int Process::nextProcessID_ = 1;

// absract state
class State {
public:
    // provides default implementation
    virtual void Dispatch(Process*) {};
    // provides default implementation
    virtual void Suspend(Process*) {};
    virtual void Block(Process*) {};
    virtual void unBlock(Process*) {};
    virtual int exit(Process*) { return -1; };
    virtual string report() = 0;

    void changeState(Process* c, State* s) {
        c->changeState(s);
    }
};


class Ready : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }
    void Dispatch(Process*) override;
    string report() override { return " state: Ready"; }
private:
    Ready() {}
    Ready(const Ready&) {}
    Ready& operator=(const Ready&) {}
};


class Running : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Running;
        return onlyInstance;
    }
    void Suspend(Process*) override;
    void Block(Process*) override;
    int exit(Process*) override;
    string report() override { return " state: Running"; }
private:
    Running() {}
    Running(const Running&) {}
    Running& operator=(const Running&) {}
};


class Blocked : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Blocked;
        return onlyInstance;
    }
    void unBlock(Process*) override;
    string report() override { return " state: Blocked"; }
private:
    Blocked() {}
    Blocked(const Blocked&) {}
    Blocked& operator=(const Blocked&) {}
};

class Exit : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Exit;
        return onlyInstance;
    }
    string report() override { return " state: Exited"; }
private:
    Exit() {}
    Exit(const Exit&) {}
    Exit& operator=(const Exit&) {}
};


// state transitions member functions
// Ready
void Ready::Dispatch(Process* c) {
    changeState(c, Running::instance());
}

//Running
void Running::Suspend(Process* c) {
    changeState(c, Ready::instance());
}

void Running::Block(Process* c) {
    changeState(c, Blocked::instance());
}

int Running::exit(Process* c) {
    changeState(c, Exit::instance());
    return 0;
}

// Blocked
void Blocked::unBlock(Process* c) {
    changeState(c, Ready::instance());
}



// Process member functions
Process::Process(State* prototype) : processID_(getNextProcessID()), state_(prototype) {}

// handles/behaviors
void Process::Dispatch() { state_->Dispatch(this); }
void Process::Suspend() { state_->Suspend(this); }
void Process::Block() { state_->Block(this); }
void Process::unBlock() { state_->unBlock(this); }
string Process::report() { return "Process " + to_string(processID_) + " is in" + state_->report(); }
int Process::exit() { return state_->exit(this); }

int main() {
    Process process(Ready::instance());
    
    cout <<  process.report() << endl;
    
    while (process.report().find("exit") == string::npos) {
        cout << "What would you like Process to do? Block, Dispatch, exit, Suspend, or unblock? [b/d/e/s/u] ";
        char action; cin >> action;
        if (action == 'b')
            process.Block();
        else if (action == 'd')
            process.Dispatch();
        else if (action == 'e')
            if (process.exit() != 0) {
                continue;
            }
            else{
                cout << "exiting..."<<endl;
                break;
            }
        else if (action == 's')
            process.Suspend();
        else
            process.unBlock();
        cout  << process.report() << endl;
    }

    Process process2(Ready::instance());
    cout << process2.report();
}
