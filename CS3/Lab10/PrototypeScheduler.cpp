// Julia Pangonis
/*
#include <iostream>
#include <string>
#include <queue>
using std::cin; using std::cout; using std::endl; using std::string;
using std::to_string; using std::queue;

class State;

// context
class Process {
public:
    Process(State* prototype);
    Process* clone();

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

    int getProcessID() const { return processID_; };

    // part of implementation of state pattern
    void changeState(State* state) { state_ = state; }
private:
    State* state_;
    int processID_;
    static int nextProcessID_;
};

int Process::nextProcessID_ = 0;

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
    cout << "dispatching..."<<endl;
    changeState(c, Running::instance());
}

//Running
void Running::Suspend(Process* c) {
    cout << "suspending..." << endl;
    changeState(c, Ready::instance());
}

void Running::Block(Process* c) {
    cout << "blocking..." << endl;
    changeState(c, Blocked::instance());
}

int Running::exit(Process* c) {
    cout << "exiting..." << endl;
    changeState(c, Exit::instance());
    return 0;
}

// Blocked
void Blocked::unBlock(Process* c) {
    cout << "unblocking..." << endl;
    changeState(c, Ready::instance());
}

Process* Process::clone() {
    Process* newProcess = new Process(state_);
    cout << "Process " << to_string(newProcess->processID_) << ": created" << endl<< newProcess->report() << endl;
    return newProcess;
}

Process::Process(State* prototype) : processID_(getNextProcessID()), state_(prototype) {}


// handles/behaviors
void Process::Dispatch() { state_->Dispatch(this); }
void Process::Suspend() { state_->Suspend(this); }
void Process::Block() { state_->Block(this); }
void Process::unBlock() { state_->unBlock(this); }
string Process::report() { return "Process " + to_string(processID_) + state_->report(); }
int Process::exit() { return state_->exit(this); }

void runScheduler(queue<Process*>& ready, queue<Process*>& blocked, int exitCount) {
    Process* runningProcess = ready.front();

    int exitedCount = 0; // Counter for exited processes

    while (exitedCount < exitCount) {
        int ranNum = rand() % 4;

        if (ranNum == 0) {
            // Process exits
            runningProcess->Dispatch();
            cout << runningProcess->report() << endl;
            runningProcess->exit();
            cout << runningProcess->report() << endl;
            exitedCount++;
            cout << endl;
            ready.pop();
        }
        else if (ranNum == 1) {
            runningProcess->Dispatch();
            cout << runningProcess->report() << endl;
            runningProcess->Suspend();
            cout << runningProcess->report() << endl;
            ready.push(runningProcess); // Move to the end of ready queue
            cout << endl;
            ready.pop();
        }
        else if (ranNum == 2){
            // Process is blocked
            runningProcess->Dispatch();
            cout << runningProcess->report() << endl;
            runningProcess->Block();
            cout << runningProcess->report() << endl;
            blocked.push(runningProcess); // Move to blocked queue
            cout << endl;
            ready.pop();
        }
        else {
            if (!blocked.empty()) {
                Process* unblockedProcess = blocked.front();
                blocked.pop();
                unblockedProcess->unBlock();
                cout << unblockedProcess->report() << endl;
                ready.push(unblockedProcess);
                cout << endl;
            }
        }

        // Check if the ready queue is empty
        if (ready.empty()) {
            cout << "The ready queue is empty." << endl << endl;
            if (blocked.empty()) {
                cout << "all processes exited." << endl;
                break;
            }
            else {
                // Move a process from blocked to ready if the blocked queue is not empty
                Process* unblockedProcess = blocked.front();
                blocked.pop();
                unblockedProcess->unBlock();
                cout << unblockedProcess->report() <<endl;
                ready.push(unblockedProcess);
                cout << endl;
            }
        }

        // Get the next process from the ready queue
        runningProcess = ready.front();
    }
}



int main() {
    srand(time(nullptr));
    queue<Process*> ready;

    queue<Process*> blocked;

    Process prototype(Ready::instance());

    for (int i = 1; i <= 4; ++i) {
        Process* newProcess = prototype.clone();
        ready.push(newProcess); 
    }
    
    cout << endl << endl << "----------- scheduler running -------------" << endl;
    
    runScheduler(ready, blocked, ready.size());

    // Clean up any remaining processes
    while (!ready.empty()) {
        Process* process = ready.front();
        ready.pop();
    }

    while (!blocked.empty()) {
        Process* process = blocked.front();
        blocked.pop();
    }

    cout << "----------scheduler done------------";
}
*/