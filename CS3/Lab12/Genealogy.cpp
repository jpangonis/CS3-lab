// Lab12.cpp 

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string;
using std::vector;

class Person { // component
public:
    Person(string firstName, Person* spouse, Person* father, Person* mother) :
        firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
    const string getFirstName() { return firstName_; }
    void setFirstName(string middle) { firstName_ = firstName_ + ' ' + middle; };
    Person* getSpouse() const { return spouse_; }
    void setSpouse(Person* spouse) { spouse_ = spouse; }
    Person* getFather() const { return father_; }
    Person* getMother() const { return mother_; }

    virtual void accept(class PersonVisitor*) = 0;
    virtual ~Person() {}
private:
    string firstName_;
    Person* spouse_;
    Person* father_;
    Person* mother_;
};


// leaf
// man has a last name
class Man : public Person {
public:
    Man(string lastName, string firstName, Person* spouse,
        Person* father, Person* mother) :
        lastName_(lastName),
        Person(firstName, spouse, father, mother) {}
    const string& getLastName() const { return lastName_; }
    void accept(class PersonVisitor* visitor) override;
private:
    const string lastName_;
};

// composite
// woman has a list of children
class Woman : public Person {
public:
    Woman(vector<Person*> children,
        string firstName,
        Person* spouse,
        Person* father, Person* mother) :
        children_(children),
        Person(firstName, spouse, father, mother) {}
    const vector<Person*>& getChildren() const { return children_; }
    void setChildren(const vector<Person*>& children) { children_ = children; }
    void accept(class PersonVisitor* visitor) override;
private:
    vector<Person*> children_;
};

// abstract visitor
class PersonVisitor {
public:
    virtual void visit(Man*) = 0;
    virtual void visit(Woman*) = 0;
    virtual ~PersonVisitor() {}
};

// visitor method for the leaf
void Man::accept(PersonVisitor* visitor) {
    visitor->visit(this);
}

// visitor method for the component: executes visits and
// defines traversal
void Woman::accept(PersonVisitor* visitor) {
    // children traversal through mother only
    // father's children are not traversed so as not
    // to traverse them twice: for mother and father

    visitor->visit(this);

    // traversing descendants
    for (auto child : children_)
        child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her
// spouse if she is married
// or by her father if she is not
class NamePrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << " " << m->getLastName() << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << " ";
        if (w->getSpouse() != nullptr)
            cout << static_cast<Man*>(w->getSpouse())->getLastName();
        else if (w->getFather() != nullptr)
            cout << static_cast<Man*> (w->getFather())->getLastName();
        else
            cout << "Doe";
        cout << endl;
    }
};


class ChildrenPrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << ": ";
        Woman* spouse = static_cast<Woman*>(m->getSpouse());
        if (spouse != nullptr)
            printNames(spouse->getChildren());
        cout << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << ": ";
        printNames(w->getChildren());
        cout << endl;
    }
private:
    void printNames(const vector<Person*>& children) {
        for (const auto c : children)
            cout << c->getFirstName() << ", ";
    }
};

class NameUpdater : public PersonVisitor {
public:
    void visit(Man* m) override {
        Person* father = m->getFather();
        if (father) {
            auto x = father->getFirstName();
            size_t spacePos = x.find(' ');
            if (spacePos != string::npos) {
                x = x.substr(0, spacePos);
            }
            m->setFirstName(x);
        }
    }

    void visit(Woman* w) override {
        Person* mother = w->getMother();
        if (mother) {
            auto x = mother->getFirstName();
            size_t spacePos = x.find(' ');
            if (spacePos != string::npos) {
                x = x.substr(0, spacePos);
            }
            w->setFirstName(x);
        }
    }
};



// demonstrating the operation
int main() {

    // setting up the genealogical tree
    // the tree is as follows
    //
    //
    //       James Smith  <--spouse-->   Mary
    //	                                  |
    //	                                 children -------------------------
    //	                                  |              |                |
    //	                                  |              |                |
    //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
    //	                                  |
    //	                                 children------------
    //	                                  |                 |
    //                                     |                 |
    //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
    //	       |
    //	     children
    //	       |
    //          |
    //	     Susan


    // first generation
    Man* js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman* ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);

    // second generation
    Woman* ps = new Woman({}, "Patricia", nullptr, js, ms);
    Man* wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);

    vector<Person*> marysKids = { ps,
                       new Man("Smith", "Robert", nullptr, js, ms),
                       new Woman({}, "Linda", nullptr, js, ms) };
    ms->setChildren(marysKids);

    // third generation
    Man* mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person*> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) };
    ps->setChildren(patsKids);

    Woman* jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person*> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);


    // defining two visitors
    ChildrenPrinter* cp = new ChildrenPrinter;
    NamePrinter* np = new NamePrinter;
    NameUpdater* updater = new NameUpdater;

    ms->accept(updater);
    // executing the traversal with the composite
    // and the specific visitor


    cout << "\nNAME LIST\n";
    ms->accept(np);
    cout << endl << endl;



    cout << "CHILDREN LIST\n";
    ms->accept(cp);



    cout << "\nJAMES' CHILDREN\n";
    js->accept(cp);

}
