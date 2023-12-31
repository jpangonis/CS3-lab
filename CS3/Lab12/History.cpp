//Julia Pangonis

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string; using std::stack;
using std::cout; using std::cin; using std::endl;

// abstract command
class Command {
public:
    Command(class Document* doc) : doc_(doc) {}
    virtual void execute() = 0; //execute the given command
    virtual void unexecute() = 0; //used for undo
    virtual void show() const = 0;
    virtual ~Command() {}
protected:
    Document* doc_;
};

// receiver
class Document {
public:
    Document(const vector <string>& lines = {}) : lines_(lines) {}

    // actions
    void insert(int line, const string& str) {
        const int index = line - 1;
        if (index <= lines_.size())
            lines_.insert(lines_.begin() + index, str);
        else
            cout << "line out of range" << endl;
    }

    const string remove(int line) {
        const int index = line - 1;
        string deletedLine = "";
        if (index < lines_.size()) {
            deletedLine = *(lines_.begin() + index); // same thing but with iterator arithmetic
            lines_.erase(lines_.begin() + index);
        }
        else
            cout << "line out of range" << endl;
        return deletedLine;
    }

    void show() const {
        for (int i = 0; i < lines_.size(); ++i)
            cout << i + 1 << ". " << lines_[i] << endl;
    }

    class Memento* createMemento() const;
    void rollBack(class Memento*);
private:
    vector<string> lines_;
};

class Memento {
public:
    Memento(const Document& doc) : doc_(doc) {}
    const Document& getState() const { return doc_; }
private:
    const Document doc_;
};

Memento* Document::createMemento() const {
    return new Memento(*this); // copying the Document itself
}

void Document::rollBack(Memento* mem) {
    *this = mem->getState();  // copying back
}

// two concrete commands
class InsertCommand : public Command {
public:
    InsertCommand(Document* doc, int line, const string& str) :
        Command(doc), line_(line), str_(str) {}
    void execute() override { doc_->insert(line_, str_); }
    void unexecute() override { doc_->remove(line_); }
    void show() const override {
        cout << "insert \"" << str_ << "\" at line " << line_ << std::endl;
    }
private:
    int line_;
    string str_;
};

class EraseCommand : public Command {
public:
    EraseCommand(Document* doc, int line) :
        Command(doc), line_(line), str_("") {}
    void execute() override { str_ = doc_->remove(line_); }
    void unexecute() override { doc_->insert(line_, str_); }
    void show() const override {
        cout << "erase line " << line_ << std::endl;
    }
private:
    int line_;
    string str_;
};


class DocumentWithHistory {
public:
    DocumentWithHistory(const vector<string>& text = {}) : doc_(text), checkpoint_(nullptr) {}

    void insert(int line, string str) {
        Command* com = new InsertCommand(&doc_, line, str);
        com->execute();
        doneCommands_.push(com);
    }

    void erase(int line) {
        Command* com = new EraseCommand(&doc_, line);
        com->execute();
        doneCommands_.push(com);
    }

    void undo() {
        if (doneCommands_.size() != 0) {
            Command* com = doneCommands_.top();
            doneCommands_.pop();
            com->unexecute();
        }
        else
            cout << "no commands to undo" << endl;
    }

    void redo(int line) {
        undoneCommands_ = doneCommands_;
        int count = 0;
        if (undoneCommands_.size() != 0) {
            while (!undoneCommands_.empty()) {
                if (count == line - 1) {
                    Command* com = undoneCommands_.top();
                    undoneCommands_.pop();
                    com->execute();
                    count++;
                    doneCommands_.push(com);
                }
                else {
                    undoneCommands_.pop();
                    count++;
                }
            }
        }
        else
            cout << "no commands to redo" << endl;
    }

    void checkpoint() {
        checkpoint_ = new Memento(doc_);
        while (!doneCommands_.empty())
            doneCommands_.pop();
    }

    void rollback() {
        if (checkpoint_ != nullptr) {
            doc_.rollBack(checkpoint_);
            delete checkpoint_;
            checkpoint_ = nullptr;
        }
        else
            cout << "No checkpoint created" << endl;
    }

    void show() const { doc_.show(); }

    // Modify the showHistory method
    void showHistory() const {
        int count = 1;
        std::stack<Command*> temp = doneCommands_;
        while (!temp.empty()) {
            cout << count << ". ";
            temp.top()->show();
            temp.pop();
            ++count;
        }
    }

private:
    Document doc_;
    stack<Command*> doneCommands_;
    stack<Command*> undoneCommands_;
    Memento* checkpoint_;

};

int main() {
    DocumentWithHistory his({
        "Lorem Ipsum is simply dummy text of the printing and typesetting",
        "industry. Lorem Ipsum has been the industry's standard dummy text",
        "ever since the 1500s, when an unknown printer took a galley of",
        "type and scrambled it to make a type specimen book. It has",
        "survived five centuries." });

    char option;
    do {
        his.show();
        cout << endl;

        cout << "Enter option (i)nsert line, (e)rase line, "
            "(u)ndo last command, (c)heckpoint, roll(b)ack, "
            "(h)istory, (r)edo command: ";
        cin >> option;

        int line; string str;
        switch (option) {
        case 'i':
            cout << "line number to insert: ";
            cin >> line;
            cout << "line to insert: ";
            cin.get();
            getline(cin, str);
            his.insert(line, str);
            break;
        case 'e':
            cout << "line number to remove: ";
            cin >> line;
            his.erase(line);
            break;
        case 'u':
            his.undo();
            break;
        case 'c':
            his.checkpoint();
            break;
        case 'b':
            his.rollback();
            break;
        case 'h':
            his.showHistory();
            cout << endl;
            break;
        case 'r':
            cout << "Choose a command history line to redo:" << endl;
            his.showHistory();
            cout << "line number to redo: ";
            cin >> line;
            cout << endl;
            his.redo(line);
            break;
        }
    } while (option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r');
}