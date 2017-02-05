#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <fstream>
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"
using namespace std;

int main(int argc, char** argv){
	HuffmanEncoder x;
	x.encode();
	HuffmanDecoder y;
	y.decode();

	system("pause");
	return 0;
}
