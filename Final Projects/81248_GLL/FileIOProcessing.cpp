#include "FileIOProcessing.h"

char* readfile(const string& filename)
{
	char* byteArray = nullptr;
	streampos size;
	ifstream file(filename, std::ios::in |
							std::ios::binary |
							std::ios::ate);
	if(file.is_open())
	{
		size = file.tellg();
		byteArray = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(byteArray, size);
		return byteArray;
	}
	return 0;
}

string readTextFile(const string& filename)
{
	ifstream file(filename);
	stringstream ss;
	ss << file.rdbuf();
	string text = ss.str();
	return text;
}

int writeStringToFile(const string& filename, const string& data)
{
	ofstream file(filename, std::ios::out |
							std::ios::trunc);
	if(file.is_open())
	{
		file<<data;
		return 0;
	}
	return -1;
}

int appendEncodedString(const string& filename, const char* data, int stringLength, int dataSize)
{
	ofstream file(filename, std::ios::out |
							std::ios::binary |
							std::ios::app);
	if(file.is_open())
	{
		file<<stringLength<<' ';
		file<<dataSize<<' ';
		file.write(data, dataSize);
		return 0;
	}
	return -1;
}

string byteToBinaryString(const char byte)
{
	bitset<8> conversion(byte);
	string binaryString = conversion.to_string();
	return binaryString;
}

string byteArrayToBinaryString(const char* byteArray, int dataSize)
{
	string binaryString;
	for(int i = 0; i < dataSize; ++i)
	{
		binaryString += byteToBinaryString(byteArray[i]);
	}
	return binaryString;
}

char* binaryStringToByteArray(const string& binaryString)
{
	int stringLength = binaryString.length();
	bitset<8> conversion;
	char* byteArray = new char[stringLength / 8];
	for(int i = 0; i < stringLength; i += 8)
	{
		conversion = bitset<8>(binaryString, i, 8);
		byteArray[i / 8] = conversion.to_ulong();
	}
	return byteArray;
}
