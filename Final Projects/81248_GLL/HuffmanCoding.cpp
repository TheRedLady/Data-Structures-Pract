#include "HuffmanCoding.h"

map<char, int> mapCharOccurences(const string& text)
{
	map<char, int> occurences;
	for(char c : text)
	{
		++occurences[c];
	}
	return occurences;
}

//should add sane file checks
int writeOccurencesToFile(map<char, int> occurences, const string& filename)
{
	ofstream file(filename, std::ios::out |
							std::ios::binary |
							std::ios::trunc); 
	file<<occurences.size()<<' ';
	for(pair<char, int> pair : occurences)
	{
		file<<pair.first<<' '<<pair.second<<' ';
	}
	return 0;
}

map<char, int> rebuildOccurencesMap(const string& data)
{
	map<char, int> occurences;
	stringstream ss(data);
	int letterCount = 0;
	char currentLetter = 0;
	int currentCount = 0;

	ss>>letterCount;
	ss.get();

	for(int i = 0; i < letterCount; ++i)
	{
		currentLetter = ss.get();
		ss>>currentCount;
		occurences[currentLetter] = currentCount;
		ss.get();
	}

	return occurences;
}

int numberOfDigitsOfNumber(unsigned int num)
{
	int numberOfDigits = (num < 10) ? 1 :
						 (num < 100) ? 2 :
						 (num < 1000) ? 3 :
						 (num < 10000) ? 4 :
						 (num < 100000) ? 5 :
						 (num < 1000000) ? 6 :
						 (num < 10000000) ? 7 :
						 (num < 100000000) ? 8 :
						 (num < 1000000000) ? 9 : 10;
	return numberOfDigits;
}

int calculateByteArrayStart(const string& text, int letterCount)
{
	unsigned int number = 0;
	int byteArrayStart = 0;
	stringstream ss(text);
	ss>>number;
	byteArrayStart += numberOfDigitsOfNumber(number); //don't add one because we will subtract at the end to make it 0-based
	ss.get();

	for(int i = 0; i < letterCount; ++i)
	{
		ss.get();

		ss>>number;
		byteArrayStart += numberOfDigitsOfNumber(number) + 3; //add all at once

		ss.get();
	}
	return byteArrayStart;
}

int readNumberFromStart(const string& data)
{
	int number = 0;
	stringstream ss(data);
	ss>>number;
	return number;
}

//should add sane file checks
//but it will look ugly
int encodeFile(const string& input, const string& output)
{
	string filedata = readTextFile(input);
	int stringLength = filedata.length();
	map<char, int> occurences = mapCharOccurences(filedata);
	Node* tree = buildTreeFromMap(occurences);
	unordered_map<char, string> binaryMapping = charToBinaryMapping(tree, occurences);

	string encodedString = encodeString(tree, filedata, binaryMapping);
	char* byteArray = binaryStringToByteArray(encodedString);

	writeOccurencesToFile(occurences, output);
	appendEncodedString(output, byteArray, stringLength, encodedString.length() / 8);

	delete[] byteArray;
	deleteTree(tree);

	return 0;
}

int decodeFile(const string& input, const string& output)
{
	char* filedata = readfile(input);
	map<char, int> occurences = rebuildOccurencesMap(filedata);
	Node* tree = buildTreeFromMap(occurences);
	unordered_map<char, string> binaryMapping = charToBinaryMapping(tree, occurences);

	int byteArrayStart = calculateByteArrayStart(filedata, occurences.size());
	int stringLength = readNumberFromStart(filedata + byteArrayStart);
	int byteArrayLength = readNumberFromStart(filedata + byteArrayStart + numberOfDigitsOfNumber(stringLength) + 1);
	char* actualByteArrayStart = filedata + byteArrayStart + numberOfDigitsOfNumber(stringLength) + numberOfDigitsOfNumber(byteArrayLength) + 2;

	string encodedString = byteArrayToBinaryString(actualByteArrayStart + 1, byteArrayLength);
	string decodedString = decodeString(tree, encodedString, stringLength);

	writeStringToFile(output, decodedString);

	delete[] filedata;
	deleteTree(tree);
	return 0;
}
