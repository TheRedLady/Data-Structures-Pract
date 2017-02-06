huffmanTool : HuffmanCoding.o HuffmanTree.o FileIOProcessing.o main.o
	g++ -std=c++11 HuffmanCoding.o HuffmanTree.o FileIOProcessing.o main.o -o huffman_tool.out

tests : HuffmanCoding.o HuffmanTree.o FileIOProcessing.o tests.o
	g++ -std=c++11 HuffmanCoding.o HuffmanTree.o FileIOProcessing.o tests.o -o tests.out

HuffmanCoding.o : HuffmanCoding.cpp
	g++ -std=c++11 -c HuffmanCoding.cpp

HuffmanTree.o : HuffmanTree.cpp
	g++ -std=c++11 -c HuffmanTree.cpp

FileIOProcessing.o : FileIOProcessing.cpp
	g++ -std=c++11 -c FileIOProcessing.cpp

tests.o : tests.cpp
	g++ -std=c++11 -c tests.cpp

clean : 
	rm *.o *.out 

testsclean : 
	rm *.o *.out *_test.txt
