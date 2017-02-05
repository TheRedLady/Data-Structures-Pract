#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool isEnd(char c)
{
    int numberOfChars = 12;
    char endCharacters[] = {',', ' ', '.', '!', '?', '\t', '\n', '\v', '\r', ';', '\\', '/'};
    for (int i = 0; i < numberOfChars; ++i)
        if (c == endCharacters[i])
            return true;
    return false;
}

bool comparePairs(pair <int, string> first, pair <int, string> second)
{
    return first.first > second.first;
}

int main()
{
    ifstream fin("input.txt");
    string word = "";
    map <string, int> wordToIndex;
    map <int, string> indexToWord;
    vector <int> numberOfOccurences;
    char input;
    while (fin.good())
    {
        input = fin.get();
        if (isEnd(input))
        {
            if (word != "")
            {
                if (wordToIndex.count(word)) ++numberOfOccurences[wordToIndex[word]];
                else
                {
                    wordToIndex[word] = numberOfOccurences.size();
                    indexToWord[numberOfOccurences.size()] = word;
                    numberOfOccurences.push_back(1);
                }
                word = "";
            }
        }
        else word += input;
    }

    vector < pair <int, string> > words;

    for (int ind = 0; ind < numberOfOccurences.size(); ind++)
        words.push_back(pair <int, string> (numberOfOccurences[ind], indexToWord[ind]));

    sort(words.begin(), words.end(), comparePairs);
    cout << words.size() << endl;
    int endOfIteration = (10 > words.size()) ? words.size() : 10;
    for (int ind = 0; ind < endOfIteration; ++ind)
        cout << words[ind].second << endl;

    return 0;
}

