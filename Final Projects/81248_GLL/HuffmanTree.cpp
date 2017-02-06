#include "HuffmanTree.h"

Node::Node(const char& sCharacter, const int& sOccurenceCount, Node* sLeft, Node* sRight) :
	character(sCharacter), occurenceCount(sOccurenceCount), left(sLeft), right(sRight){}

bool GreaterNodeComparison::operator() (const Node* lhs, const Node* rhs)
{
	return (lhs->occurenceCount > rhs->occurenceCount);
}


bool hasLeft(const Node* root)
{
	return (root->left != nullptr);
}
bool hasRight(const Node* root)
{
	return (root->right != nullptr);
}
bool isLeaf(const Node* root)
{
	return (root->character != -1);
}

void printTree(Node* root)
{
	if(hasLeft(root))
	{
		printTree(root->left);
	}
	cout<<"("<<root->character<<","<<root->occurenceCount<<")"<<endl;
	if(hasRight(root))
	{
		printTree(root->right);
	}
}

void graphDotPrint(const Node* root, string filename)
{
	ofstream file;
	const int dotIndexStart = 0;

	file.open(filename);
	file<<"digraph G "<<endl<<"{"<<endl;
	graphDotPrintTree(root, file, dotIndexStart);
	file<<"}";
	file.close();
}

void graphDotPrintTree(const Node* root, ofstream& file, int id)
{
	file<<"\t"<<id<<"[label=\"";
	if(isLeaf(root))
	{
		file<<"("<<root->character<<", "<<root->occurenceCount<<")\"]"<<endl;
	}
	else
	{
		file<<root->occurenceCount<<"\"]"<<endl;
	}
	if(hasLeft(root))
	{
		file<<"\t"<<id<<" -> "<<(2*id + 1)<<endl;
		graphDotPrintTree(root->left, file, 2*id + 1);
	}
	if(hasRight(root))
	{
		file<<"\t"<<id<<" -> "<<(2*id + 2)<<endl;
		graphDotPrintTree(root->right, file, 2*id + 2);
	}
}

void deleteTree(Node* root)
{
	deleteTreeNodes(root);
	delete root;
}

void deleteTreeNodes(Node* root)
{
	if(hasLeft(root))
	{
		deleteTreeNodes(root->left);
		delete root->left;
	}
	if(hasRight(root))
	{
		deleteTreeNodes(root->right);
		delete root->right;
	}
}

Node* buildTreeFromMap(const map<char,int>& mapping)
{
	priority_queue<Node*, vector<Node*>, GreaterNodeComparison> nodeQueue;
	Node* tempFirst = nullptr;
	Node* tempSecond = nullptr;
	Node* tree = nullptr;
	for(pair<char, int> tuple : mapping)
	{
		nodeQueue.push(new Node(tuple.first, tuple.second, nullptr, nullptr));
	}
	while(nodeQueue.size() > 1)
	{
		tempFirst = nodeQueue.top();
		nodeQueue.pop();
		tempSecond = nodeQueue.top();
		nodeQueue.pop();
		
		nodeQueue.push(new Node(-1, tempFirst->occurenceCount + tempSecond->occurenceCount, 
									tempFirst, tempSecond));
	}
	tree = nodeQueue.top();
	return tree;
}

//optimise, currently very slow because of all that copying
//and prepending to strings, possibly just use a list
//and a stack of operations to emulate recursion, avoiding 
//copy constr and prepending, but then again this recursion
//is kinda cool looking
string encodeCharacter(const Node* root, const char& character)
{
	if(isLeaf(root))
	{
		if(root->character == character)
		{
			return string();
		}
		else
		{
			return string("n");
		}
	}
	string childrenCheck;

	childrenCheck = encodeCharacter(root->left, character);
	if(childrenCheck.empty() || childrenCheck[0] != 'n')
	{
		return string("0") += childrenCheck;
	}

	childrenCheck = encodeCharacter(root->right, character);
	if(childrenCheck.empty() || childrenCheck[0] != 'n')
	{
		return string("1") += childrenCheck;
	}
	return string("n");
}



//could remove the map that is being passed here 
//by just finding the leaves of the tree and adding them to a map
//but this would require passing a reference in the recursive function
//and making it void both of which I don't like looking at
unordered_map<char, string> charToBinaryMapping(const Node* tree, const map<char, int>& occurences)
{
	unordered_map<char, string> mapping;

	for(pair<char, int> pair : occurences)
	{
		mapping[pair.first] = encodeCharacter(tree, pair.first);
	}
	return mapping;
}

//could remove the mapping from here, same reason as above, also this is more in line with
//how the rest of my code looks, not entirely sure what's better
string encodeString(const Node* tree, const string& originalString, const unordered_map<char, string>& mapping)
{
	string encodedString;
	for(char c : originalString)
	{
		encodedString += mapping.at(c);
	}
	while((encodedString.length() % 8) != 0)
	{
		encodedString += '0';
	}
	return encodedString;
}

string decodeString(const Node* tree, const string& encodedString, const int& stringLength)
{
	string decodedString;
	const Node* walk = tree;
	int decodedCharacters = 0;

	decodedString.reserve(stringLength);

	for(char c : encodedString)
	{
		if(c == '0')
		{
			walk = walk->left;
		}
		else
		{
			walk = walk->right;
		}
		if(isLeaf(walk))
		{
			decodedString += walk->character;
			walk = tree;
			++decodedCharacters;
			if(decodedCharacters == stringLength)
			{
				return decodedString;
			}
		}
	}
	return decodedString;
}

