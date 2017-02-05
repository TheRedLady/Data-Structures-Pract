// 3. Симулация на опашка в банка
// Целта на тази симулация е да изгради представа у управителя на банка за ефективността на обслужването на случайно пристигащи в банката клиенти от определен брой касиери, както и за броя и времето за обслужване на клиенти от всеки касиер.
// Когато клиент пристига в банката и всички касиери са заети, той се нарежда на опашката, като получава уникален номер, съвпадащ с минутата на пристигането му (от едно до МАХ). Приемаме, че за 1 минута пристига не повече от 1 клиент. 
// Да се напише програма, която симулира обслужването на опашка от клиенти за интервал от време между 200 и 500 минути (случайно избран интервал при стартиране). Броят касиери е между 3 и 10 (случайно избран при стартиране). Клиенти постъпват в случайно избрани интервали от време, техният брой е случаен и се избира при стартиране на програмата. Времето за обслужване на всеки клиент също е случайно.
// В края на изпълнението на програмата да се изведе статистика за:
// 	-общ брой обслужени клиенти
// 	-брой обслужени клиенти от всеки касиер
// 	-средно време за чакане в опашката
// 	-средна дължина на опашката
// 	-максимална дължина на опашката



#include <iostream>
#include <queue>
#include <ctime>

using namespace std;




class Customer{
private:
	int id;
	int waitTime;
public:

	Customer(int id, int waitTime){
		setId(id);
		setWaitTime(waitTime);
	}

	int getId(){
		return this->id;
	}
	void setId(int id){
		this->id = id;
	}
	int getWaitTime(){
		return this->waitTime;
	}
	void setWaitTime(int waitTime){
		this->waitTime = waitTime;
	}
	bool reduceWaitTime(){
		if(this->waitTime>0){
			this->waitTime--;
			return false;
		}else{
			return true;
		}
	}


};

class Banker {
private:
	int totalCustomers = 0;
	bool busy = false;
	Customer* currentCustomer;

public:
	bool isBusy(){
		return this->busy;
	}
	void setIsBusy(bool busy){
		this->busy = busy;
	}
	void increaseTotalCustomers(){
		this->totalCustomers++;
	}
	int getTotalCustomers(){
		return this->totalCustomers;
	}
	void setCurrentCustomer(Customer* customer){
		this->currentCustomer = customer;
	}
	Customer* getCurrentCustomer(){
		if(this->currentCustomer){
			return this->currentCustomer;
		}else{
			return NULL;
		}
	}
};


int main(){

	srand((unsigned int) time (NULL));

	int N = 200 + rand()%301;
	int maxN = N;

	int bankersCount = 3 + rand()%8;
	Banker *bankers = new Banker[bankersCount];
	

	queue<Customer*> bankQueue;

	int totalCustomers = 0;
	int maxQueueSize = 0;
	int averageQueueSize = 0;
	double averageWaitTime = 0;

	cout<<"Time interval: "<<N<<endl;
	cout<<"Bankers: "<<bankersCount<<endl;

	while(N>0){

		if(rand()%3){
			bankQueue.push(new Customer(maxN - N, 1+ rand()%10));
		}

		for (int i = 0; i < bankersCount; ++i)
		{
			if(bankers[i].isBusy()){
				if(bankers[i].getCurrentCustomer()->reduceWaitTime()){
					bankers[i].setIsBusy(false);
					bankers[i].setCurrentCustomer(NULL);
					bankers[i].increaseTotalCustomers();
				}
			}
		}

		for (int i = 0; i < bankersCount; ++i)
		{
			if(!bankQueue.empty()){
				if(!bankers[i].isBusy()){
					bankers[i].setIsBusy(true);
					bankers[i].setCurrentCustomer(bankQueue.front());
					averageWaitTime += bankQueue.front()->getWaitTime();
					bankQueue.pop();
				}
			}else{
				break;
			}
		}


		if(maxQueueSize<bankQueue.size()){
			maxQueueSize = bankQueue.size();
		}
		

		averageQueueSize +=bankQueue.size();


		
	
		N--;
	}
	for (int i = 0; i < bankersCount; ++i)
	{
		totalCustomers += bankers[i].getTotalCustomers();
		cout<<bankers[i].getTotalCustomers()<<" obslujeni klienta ot banker "<<i+1<<"."<<endl;
	}
	cout<<"Total customers: "<<totalCustomers<<endl;
	cout<<"Max queue size: "<<maxQueueSize<<endl;
	cout<<"Average queue size: "<<averageQueueSize/maxN<<endl;
	cout<<"Average wait time: "<<averageWaitTime/totalCustomers<<endl;
	delete [] bankers;
	return 0;
}