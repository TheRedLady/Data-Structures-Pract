#include <iostream>
#include <queue>
using namespace std;

class Client{
private:
	int minuteOfArrival;
	int timeOfService;
	int minuteOfEnd;
public:
	Client(){
		minuteOfArrival = 0;
		timeOfService = 0;
		minuteOfEnd = 0;
	}

	Client(int m, int t){
		this->minuteOfArrival = m;
		this->timeOfService = t;
		this->minuteOfEnd = this->minuteOfArrival + this->timeOfService;

	}

	Client(const Client& other){
		this->minuteOfArrival = other.minuteOfArrival;
		this->timeOfService = other.timeOfService;
		this->minuteOfEnd = other.minuteOfEnd;
	}

	~Client(){

	}

	Client& operator=(const Client& other){
		if (this != &other){
			delete this;
			this->minuteOfArrival = other.minuteOfArrival;
			this->timeOfService = other.timeOfService;
			this->minuteOfEnd = other.minuteOfEnd;
		}
	}

	void setMinuteOfArrival(int m){
		this->minuteOfArrival = m;
	}

	void setTimeOfService(int t){
		this->timeOfService = t;
	}

	void setMinuteOfEnd(int e){
		this->minuteOfEnd = e;
	}

	int getMinuteOfArrival(){
		return this->minuteOfArrival;
	}

	int getTimeOfService(){
		return this->timeOfService;
	}

	int getEnd(){
		return this->minuteOfEnd;
	}

};