#include <iostream>
#include <vector>

using namespace std;

class DoubleStack {
private:
	vector<int> ds;
	//TODO - разделител
public:
	DoubleStack() {
		
	}
	void push1(int x) {
		ds.insert(ds.begin(),x);
	}
	void push2(int x) {
		ds.push_back(x);
	}
	void pop1() {
		//if(разделител минат)
		ds.erase(ds.begin());
	}
	void pop2() {
		//if(разделител минат)
		ds.erase(ds.end());
	}
};