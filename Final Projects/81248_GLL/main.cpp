#include "HuffmanTree.h"
#include "FileIOProcessing.h"
#include "HuffmanCoding.h"

using std::cin;

int main(int argc, char** argv)
{
	char function = 0;
	string input;
	string output;
	if(argc != 4)
	{
		cout<<"(E)ncoding or (D)ecoding?"<<endl;
		cin>>function;
		while(function != 'E' &&
			  function != 'D' &&
			  function != 'e' &&
			  function != 'd')
		{
			cout<<"(E)ncoding or (D)ecoding?"<<endl;
			cin>>function;
		}
		cout<<"Input filename:"<<endl;
		cin>>input;
		cout<<"Output filename:"<<endl;
		cin>>output;
		if(function == 'E' || function == 'e')
		{
			encodeFile(input, output);
		}
		else
		{
			decodeFile(input, output);
		}
	}
	else
	{
		function = argv[1][0];
		if(function == 'E' || function == 'e')
		{
			encodeFile(input, output);
		}
		else if(function == 'D' || function == 'd')
		{
			decodeFile(input, output);
		}
		else
		{
			cout<<"Invalid operation."<<endl;
		}
	}
	return 0;
}
