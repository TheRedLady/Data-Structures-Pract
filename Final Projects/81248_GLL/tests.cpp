#include "HuffmanTree.h"
#include "FileIOProcessing.h"
#include "HuffmanCoding.h"
//tests

//already wrote a lot with just eye checking
//and some of them can't be done with assert
//so I'm too lazy to rewrite with asserts
void makeTreeTest()
{
	cout<<"//makeTreeTest//"<<endl;
	map<char,int> testing;
	testing['a'] = 25;
	testing['c'] = 100;
	testing['z'] = 99;
	testing['k'] = 7;
	testing['o'] = 9;
	Node* treeTest = buildTreeFromMap(testing);
	deleteTree(treeTest);
	cout<<endl;
}

void dotTest()
{
	cout<<"//dotTest//"<<endl;
	map<char,int> testing;
	testing['a'] = 25;
	testing['c'] = 100;
	testing['z'] = 99;
	testing['k'] = 7;
	testing['w'] = 200;
	testing['o'] = 9;
	Node* treeTest = buildTreeFromMap(testing);
	graphDotPrint(treeTest, "./dotprint/tree.dot");
	deleteTree(treeTest);
	cout<<endl;
}

void mappingAndDecodeTest()
{
	cout<<"//mappingAndDecodeTest//"<<endl;
	map<char,int> testing;
	testing['a'] = 25;
	testing['c'] = 100;
	testing['z'] = 99;
	testing['k'] = 7;
	testing['w'] = 200;
	testing['o'] = 9;
	Node* treeTest = buildTreeFromMap(testing);
	unordered_map<char, string> mapping = charToBinaryMapping(treeTest, testing);
	for(pair<char, string> pair : mapping)
	{
		cout<<pair.first<<" -> "<<mapping[pair.first]<<endl;
	}
	string test("1100010111110010");
	cout<<decodeString(treeTest, test, 4)<<endl;
	deleteTree(treeTest);
	cout<<endl;
}

void encodeDecodeTest()
{
	cout<<"//encodeDecodeTest//"<<endl;
	map<char,int> testing;
	testing['a'] = 25;
	testing['c'] = 100;
	testing['z'] = 99;
	testing['k'] = 7;
	testing['o'] = 9;
	Node* treeTest = buildTreeFromMap(testing);
	string testOriginalString = "cakozzzakoczzzz";

	unordered_map<char, string> mapping = charToBinaryMapping(treeTest, testing);

	string encodedString = encodeString(treeTest, testOriginalString, mapping);
	string decodedString = decodeString(treeTest, encodedString, testOriginalString.length());
	cout<<decodedString<<endl;
	deleteTree(treeTest);
	cout<<endl;
}

//TODO
void fileIOTests()
{
}

void binaryStringByteArrayTests()
{
	cout<<"//binaryStringByteArrayTests//"<<endl;
	char bytetest[5] = {1, 3, 5, 7, 9};
	char* backToArrayTest;
	string stringTest = byteArrayToBinaryString(bytetest, 5);
	cout<<stringTest<<endl;
	backToArrayTest = binaryStringToByteArray(stringTest);
	for(int i = 0; i < 5; i++)
	{
		cout<<(int)backToArrayTest[i]<<" ";
	}
	delete[] backToArrayTest;
	cout<<endl;
}

void encodeDecodeFileTest()
{
	cout<<"//encodeDecodeFileTest//"<<endl;
	encodeFile("lorem_ipsum.txt", "encode_test.txt");
	decodeFile("encode_test.txt", "decode_test.txt");
}



int main(int argc, char** argv)
{
	makeTreeTest();
	dotTest();
	mappingAndDecodeTest();
	encodeDecodeTest();
	fileIOTests();
	binaryStringByteArrayTests();
	encodeDecodeFileTest();
	return 0;
}
