#ifndef __FILE_IO_PROCESSING__
#define __FILE_IO_PROCESSING__

#include <string>
#include <fstream>
#include <bitset>
#include <sstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::streampos;
using std::bitset;
using std::stringstream;

char* readfile(const string& filename);
string readTextFile(const string& filename);
int writeStringToFile(const string& filename, const string& data);
int appendEncodedString(const string& filename, const char* data, int stringLength, int dataSize);

string byteToBinaryString(const char* byte);

string byteArrayToBinaryString(const char* byteArray, int size);
char* binaryStringToByteArray(const string& binaryString);

#endif
