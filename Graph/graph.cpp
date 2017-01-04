#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Vertex {
    typedef pair<int, Vertex*> Edges;
    vector<Edges> adj; 
    string name;
    Vertex(string s) : name(s) {}
};

 //cost of edge, destination vertex
typedef unordered_map<string, Vertex*> GraphMap;

class Graph
{
    public:
        GraphMap graph;
        void addVertex(const string&);
        void addEdge(const string& from, const string& to, int cost);
};

void Graph::addVertex(const string &name)
{
    GraphMap::iterator itr = graph.find(name);
    if (itr == graph.end())
    {
        Vertex* v;
        v = new Vertex(name);
        graph[name] = v;
        return;
    }
}

void Graph::addEdge(const string& from, const string& to, int cost)
{
    Vertex* f = (graph.find(from)->second);
    Vertex* t = (graph.find(to)->second);
    pair<int, Vertex*> edge = make_pair(cost, t);
    f->adj.push_back(edge);
}

int main(){

    Graph test;
    test.addVertex("A");
    test.addVertex("B");
    test.addVertex("C");

    test.addEdge("A", "B", 1);

    return 0;
}
