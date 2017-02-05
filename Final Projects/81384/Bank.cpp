#include <iostream>
#include <queue>
#include "Client.cpp"
using namespace std;

bool isEmptyQueue(queue<Client> *q, int count){
	for (int i = 0; i < count; i++)
	{
		if (q[i].empty()){
			return true;
		}
	}
	return false;
}

int bestQueue(queue<Client> *q, int count){
	int numPayDesk = 0;
	if (isEmptyQueue(q, count)){
		for (int i = 0; i < count; i++)
		{
			if (q[i].empty()){
				return i;
			}

		}
	}
	else{
		int min = q[0].back().getEnd();
		for (int i = 0; i < count; i++)
		{
			if (q[i].back().getEnd() < min){
				min = q[i].back().getEnd();
				numPayDesk = i;
			}
		}
	}
	return numPayDesk;
}

int maxLengthOfaQueue(int* q, int count){
	int max = 0;
	for (int i = 0; i < count; i++)
	{
		if (q[i]>max){
			max = q[i];
		}
	}
	return max;
}


int main(){
	bool flag = 1;


	while (flag){
		int max = rand() % 300 + 200; //random (200 - 500)
		int payDesks = rand() % 7 + 3; //random (3 - 10)
		//int numberOfClients = rand() % (max / 2) + 1; //random (1 - max/2) 
		//Poneje nqma ogranicheniq, klientite shte vlizat do kraq na rabotnoto vreme max

		cout << "Working time: " << max << " , Pay desks: " << payDesks << endl; // " , Number of clients: " << numberOfClients << endl;
		queue<Client> *queues;
		queues = new queue<Client>[payDesks];

		int *clientsForEachQueue;
		clientsForEachQueue = new int[payDesks];
		for (int i = 0; i < payDesks; i++){
			clientsForEachQueue[i] = 0;
		}
		int* timeForWaiting;
		timeForWaiting = new int[payDesks];
		for (int i = 0; i < payDesks; i++){
			timeForWaiting[i] = 0;
		}

		int minOfArrival = rand() % max / 10;
		int numberOfClients = 0;
		while (minOfArrival < max)
		{
			//pop queues

			for (int i = 0; i < payDesks; i++)
			{
				if (!queues[i].empty()){
					int last = queues[i].back().getEnd();
					if (minOfArrival > last){
						while (!queues[i].empty()){
							queues[i].pop();
						}
					}
				}
			}
			// pop queues

			int timeOfService = rand() % max / 5 + 1;
			cout << minOfArrival << "[" << timeOfService << "] , ";
			int bestQ = bestQueue(queues, payDesks);

			Client c(minOfArrival, timeOfService);
			queues[bestQ].push(c);
			clientsForEachQueue[bestQ] += 1;
			timeForWaiting[bestQ] += timeOfService;

			minOfArrival = (rand() % max / 10 + minOfArrival);
			numberOfClients++;
		}
		cout << endl << "Queues: " << endl;
		for (int i = 0; i < payDesks; i++)
		{
			cout << "Queue " << i << ":" << endl;
			while (!queues[i].empty()){
				cout << queues[i].front().getMinuteOfArrival() << "[ time: " << queues[i].front().getTimeOfService() << ", end: " << queues[i].front().getEnd() << " ], ";
				queues[i].pop();
			}
			cout << endl;
		}
		cout << "Statistics: " << endl;
		cout << "The number of clients is: " << numberOfClients << endl;
		cout << "The number of clients for each queue is: " << endl;
		for (int i = 0; i < payDesks; i++)
		{
			cout << "Queue " << i << ": " << clientsForEachQueue[i] << endl;
		}
		cout << endl;
		cout << "The middle time of waiting for each queue is: " << endl;
		for (int i = 0; i < payDesks; i++)
		{
			cout << "Queue " << i << ": " << timeForWaiting[i] / clientsForEachQueue[i] << endl;
		}
		cout << endl;
		cout << "The middle length of queues is: " << numberOfClients / payDesks << endl;
		cout << "The max length of a queue is: ";
		int maxLen = maxLengthOfaQueue(clientsForEachQueue, payDesks);
		cout << maxLen;
		cout << endl << endl << endl;

		cout << "Enter:" << endl;
		cout << "1 -> to generate new Queue in a bank" << endl;
		cout << "0 -> not to" << endl;
		cin >> flag;
	}

	cout << endl;
	system("pause");
	return 0;
}