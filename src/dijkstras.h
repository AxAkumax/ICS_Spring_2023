#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

class Compare {
public:
    bool operator()(pair<int, int> left, pair<int, int> right)
    {
        return left.second > right.second;
    }
};
 
constexpr int INF = numeric_limits<int>::max();

struct Edge {
    int src=0;
    int dst=0;
    int weight=0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend istream& operator>>(istream& in, Edge& e)
    {
        return in >> e.src >> e.dst >> e.weight;
    }

    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};

struct Graph : public vector<vector<Edge>> {
    int numVertices=0;
};

inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw runtime_error("Unable to find input file");
    G.resize(G.numVertices);
    for (Edge e; in >> e;)
        G[e.src].push_back(e);
    return in;
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous);
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination);
void file_to_graph(string filename, Graph & G);
string get_arg(int argc, char *argv[], string def);
void print_path(const vector<int>& v, int total);
