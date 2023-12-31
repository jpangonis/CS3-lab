// Julia Pangonis

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <map>
#include <algorithm>

// for timed sleep
#include <thread>
#include <chrono>


using std::cout; using std::cin; using std::endl;
using std::string; using std::isdigit;

enum class AirlineLogo { AirFrance, KLM, Aeroflot, Lufthansa, Delta, United, JetBlue };

//abstract flyweight
class airline {
public:
	virtual string takeoff(string) = 0;
	virtual string landing(string) = 0;
};

//concrete flyweights
class Delta : public airline {
public:
	string takeoff(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... DELTA" + num + " takes off...";
	}
	string landing(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... DELTA" + num + " lands...";
	}
};

class AirFrance : public airline {
public:
	string takeoff(string flight) override {
		string num = "";
		for (char c : flight) if (isdigit(c)) num += c;
		return "... AIRFRANCE" + num + " takes off...";
	}
	string landing(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... AIRFRANCE" + num + " lands...";
	}
};

class KLM : public airline {
public:
	string takeoff(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... KLM" + num + " takes off...";
	}
	string landing(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... KLM" + num + " lands...";
	}
};

class AeroFlot : public airline {
public:
	string takeoff(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... AEROFLOT" + num + " takes off...";
	}
	string landing(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... AEROFLOT" + num + " lands...";
	}
};

class Lufthansa : public airline {
public:
	string takeoff(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... LUFTHANSA" + num + " takes off...";
	}
	string landing(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... LUFTHANSA" + num + " lands...";
	}
};

class United : public airline {
public:
	string takeoff(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... UNITED" + num + " takes off...";
	}
	string landing(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... UNITED" + num + " lands...";
	}
};

class JetBlue : public airline {
public:
	string takeoff(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... JETBLUE" + num + " takes off...";
	}
	string landing(string flight) override {
		string num = "";
		for (char c : flight) {
			if (isdigit(c)) num += c;
		}
		return "... JETBLUE" + num + " lands...";
	}
};

//factory
class Factory {
public:
	static airline* makeRank(string r) {
		AirlineLogo logo;
		if (r.find("Delta") != string::npos) {
			logo = AirlineLogo::Delta;
			ranks_[logo] = new Delta;
		}
		if (r.find("AirFrance") != string::npos) {
			logo = AirlineLogo::AirFrance;
			ranks_[logo] = new AirFrance;
		}
		if (r.find("KLM") != string::npos) {
			logo = AirlineLogo::KLM;
			ranks_[logo] = new KLM;
		}
		if (r.find("Aeroflot") != string::npos) {
			logo = AirlineLogo::Aeroflot;
			ranks_[logo] = new AeroFlot;
		}
		if (r.find("Lufthansa") != string::npos) {
			logo = AirlineLogo::Lufthansa;
			ranks_[logo] = new Lufthansa;
		}
		if (r.find("United") != string::npos) {
			logo = AirlineLogo::United;
			ranks_[logo] = new United;
		}
		if (r.find("JetBlue") != string::npos) {
			logo = AirlineLogo::JetBlue;
			ranks_[logo] = new JetBlue;
		}

		return ranks_[logo];
	}

private:
	static std::map<AirlineLogo, airline*> ranks_;
};


std::map<AirlineLogo, airline*> Factory::ranks_;

class Controller {
public:
	virtual void join(class Flight*) = 0;
	virtual void leave(class Flight*) = 0;
	virtual void broadcast() = 0;
	virtual void observe() = 0;
};


// concrete mediator
// tower, runway clearance
class Tower : public Controller {
public:
	void join(class Flight*) override;
	void leave(class Flight*) override;
	void broadcast() override;
	void observe() override;
private:
	std::set<class Flight*> waiting_;
};


// abstract colleague
class Flight {
public:
	Flight(Controller* controller)
		: controller_(controller), status_(Status::waiting) {
		task_ = rand() % 2 ? Task::taxiing : Task::approaching;
		controller_->join(this);
		
		
	}
	void receive(const string& msg) {
		plane = Factory::makeRank(flightNo_);
		
		if (msg.find(flightNo_) != string::npos || msg.find("all") != string::npos) {
			if (msg.find("clear") != string::npos) {
				cout << flightNo_ << " roger that, ";
				cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
				status_ = Status::cleared;
			}
			else if (msg.find("status") != string::npos) {
				cout << flightNo_
					<< (status_ == Status::waiting ? " waiting to " : " cleared to ")
					<< (task_ == Task::taxiing ? "take off" : "land") << endl;
			}
			else
				cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
		}
	}
	bool isCleared() const { return status_ == Status::cleared; }
	void proceed() {
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1)); // wait a while    
		cout << (task_ == Task::taxiing ? plane->takeoff(flightNo_) : plane->landing(flightNo_)) << endl;
		controller_->leave(this);
	}

protected:
	string flightNo_;
	Controller* controller_;
	enum class Task { taxiing, approaching };  Task task_;
	enum class Status { waiting, cleared };    Status status_;
	airline* plane;
	AirlineLogo airlineLogo_;
};

// concrete colleagues
class Airbus : public Flight{
public:
	Airbus(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "AirFrance", "KLM", "Aeroflot", "Lufthansa" };
		flightNo_ = companies[rand() % companies.size()] +
			std::to_string(rand() % 1000);
		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};

class Boeing : public Flight{
public:
	Boeing(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "Delta", "United", "JetBlue" };
		flightNo_ = companies[rand() % companies.size()] +
			std::to_string(rand() % 1000);
		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};


// member functions for Tower
void Tower::broadcast() {
	cout << "Tower: ";
	string msg;
	getline(cin, msg);
	if (!msg.empty())
		for (auto f : waiting_) f->receive(msg);
}


void Tower::observe() {
	auto findCleared = [](Flight* f) {return f->isCleared(); };

	auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);

	while (toProceed != waiting_.end()) { // found a cleared flight
		(*toProceed)->proceed();
		toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
		if (toProceed != waiting_.end())
			cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single flight cleared
	}
}


void Tower::join(Flight* f) {
	waiting_.insert(f);
}


void Tower::leave(Flight* f) {
	waiting_.erase(f);
	delete f;
}



int main() {
	srand(time(nullptr));
	Tower jfk;

	new Boeing(&jfk);
	new Airbus(&jfk);
	new Boeing(&jfk);
	new Airbus(&jfk);

	while (true) {
		jfk.broadcast();
		jfk.observe();
		if (rand() % 2) {
			if (rand() % 2)
				new Boeing(&jfk);
			else
				new Airbus(&jfk);
		}
	}
}
