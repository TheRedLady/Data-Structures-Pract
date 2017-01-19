#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


string top10[10];
void mostCommon(string fileName){

  ifstream file;
  file.open (fileName);
  string word;
  int count, max;

  map<string,int> mymap;

  while (file >> word)
  {
    count = mymap.find(word)->second;
    if(mymap.count(word) != 0){
      mymap.erase(word);
    }
    mymap.insert ( pair<string,int>(word,count + 1) );
  }
  for (map<string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
    cout<<it->first<< " => " <<it->second<< '\n';
  }


  
  
}




int main ()
{

  
  mostCommon("example.txt");
  




  return 0;
}


