#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

void printMost10(char * inc) {
	// should be read from file
	int max10s[10] = { 0 };
	string max10Words[10];
	map<string, int> allWords;
	int incCounter = 0;	
	while (inc[incCounter]) {
		string word = "";
		while ((char)inc[incCounter] >= 97 && (char)inc[incCounter] <= 122) {
			word += inc[incCounter];
			incCounter++;
		}
		if (word.length()!=0) {
			if ((allWords.find(word) == allWords.end())) {
				allWords[word] = 1;
			}
			else {
				allWords[word]++;
			}
		}
		incCounter++;
	}
	for (map<string, int>::iterator it = allWords.begin(); it != allWords.end(); ++it) {
		for (int i = 0; i < 10; i++) {
			if (it->second > max10s[i]) {
				for (int j = 10; j >i && i>1; j--) {
					max10Words[j] = max10Words[j - 1];
					max10s[j] = max10s[j - 1];
				}
				max10Words[i] = it->first;
				max10s[i] = it->second;
				break;
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		cout << max10Words[i] <<" "<< max10s[i]<< endl;
	}
}

int main() {
	char a[] = "asf dfa safas asdfas asdfasd asdfasdf asdfa s dfa dasdfas as s s s s d d d d f f f f f asgq wqe qwe dagsy ";
	printMost10(a);
	return 0;
}
