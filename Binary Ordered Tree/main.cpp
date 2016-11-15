#include "BinaryOrderedTree.h"

int main()
{
	BOT<int> tree;
	tree.insert(5);
	tree.insert(8);
	tree.insert(3);
	tree.insert(2);
	tree.insert(7);
	tree.insert(-1);
	tree.insert(9);

	tree.print();
	tree.remove(5);
	tree.print();

	return 0;
}