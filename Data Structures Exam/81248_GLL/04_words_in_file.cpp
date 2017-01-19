#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using std::ifstream;
using std::string;
using std::map;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::sort;


string placeFileIntoString(const char* inputFilename)
{
	ifstream inputFile;
	string temp;
	string input;
	inputFile.open(inputFilename);
	while(!inputFile.eof())
	{
		getline(inputFile, temp);
		input += temp;
		input.push_back('\n');
		temp.clear();
	}
	input.erase(--input.end());
	inputFile.close();
	return input;
}

map<string, int> countWords(const string& input)
{
	string currentWord;
	string copy = input;
	map<string, int> occurences;
	int position;

	while(!copy.empty())
	{
		position = copy.find_first_not_of("\t .,!?");
		copy.erase(0, position);
		position = copy.find_first_of("\t .,!?");
		currentWord.insert(0, copy, 0, position);
		copy.erase(0, position);
		occurences[currentWord]++;
		currentWord.clear();
	}
	return occurences;
}

void countWordsInFile(const char* inputFilename)
{
	string contents = placeFileIntoString(inputFilename);
	map<string, int> occurences = countWords(contents);
	vector<pair<int, string> > dirtyHacksYo;
	for(map<string, int>::iterator it = occurences.begin(); it != occurences.end(); ++it)
	{
		dirtyHacksYo.push_back(pair<int, string>((*it).second, (*it).first));
	}
	sort(dirtyHacksYo.rbegin(), dirtyHacksYo.rend());
	for(int i = 0; i < 10; i++)
	{
		cout<<(i + 1)<<". "<<dirtyHacksYo[i].second<<" with "<<dirtyHacksYo[i].first<<" occurences."<<endl;
	}
	// LOL KEK
}

int main(int argc, char** argv)
{
	countWordsInFile(argv[1]);
	return 0;
}
