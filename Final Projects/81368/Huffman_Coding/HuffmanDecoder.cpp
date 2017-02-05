#include "BTree.h"
#include "HuffmanDecoder.h"

void HuffmanDecoder::decode(ifstream &tableCode, ifstream &codeFile, ofstream &decodeFile){
	map<char, int>table;
	vector<string> readedCharacters;
	string str = "";
	char characterToRead;

	bool chekFor = true;
	while (tableCode.get(characterToRead)){
		if (characterToRead == '#' && chekFor){
			readedCharacters.push_back(str);
			str.clear();
			chekFor = false;
		}
		else{
			str = str + characterToRead;
			chekFor = true;
		}
	}

	tableCode.close();

	for (int i = 0; i < readedCharacters.size() - 1; i += 2){
		char key = readedCharacters[i][0];
		int value = stoi(readedCharacters[i + 1], 0, 10);
		table[key] = value;
	}

	BTree tree(table);

	char charToRead;
	char symbol;
	codeFile.seekg(-1, codeFile.end);
	char bitsToRead;
	codeFile.get(bitsToRead);
	int fileLengthInBytes = codeFile.tellg();
	codeFile.clear();
	codeFile.seekg(0, ios::beg);
    for(int i =0;i<fileLengthInBytes-2;i++)
    {
		codeFile.get(charToRead);
       for (int i = 7; i >= 0; --i)
		{
		   char bit = (((charToRead >> i) & 1) + 48);
			if (tree.consumeSymbol(bit, symbol))
			{
				decodeFile << symbol;
			}
        }

    }
	codeFile.get(charToRead);
    for(int i =7;bitsToRead!=0;i--,bitsToRead--)
    	{
		char bit = (((charToRead >> i) & 1) + 48);
			if (tree.consumeSymbol(bit, symbol))
			{
				decodeFile << symbol;
			}
		}
	
		
	decodeFile.close();
	codeFile.close();
	
}

HuffmanDecoder::HuffmanDecoder(){};
void HuffmanDecoder:: decode(){
	string codeTablePath;
	string codeFilePath;
	string decodeFilePath;

	cout << "Please enter a file of the table:\n";
	cin >> codeTablePath;
	cout << "Please enter a file of the code:\n";
	cin >> codeFilePath;
	cout << "Please enter a file for the decode:\n";
	cin >> decodeFilePath;

	ifstream codeTable(codeTablePath.c_str(), std::ifstream::in | std::ifstream::binary);
	ifstream codeFile(codeFilePath.c_str(), std::ifstream::in | std::ifstream::binary);
	ofstream decodeFile(decodeFilePath.c_str(), std::ofstream::out | std::ofstream::binary);

	decode(codeTable, codeFile, decodeFile);
}

