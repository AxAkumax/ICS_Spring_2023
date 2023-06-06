#include "graph.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>

void error(string msg)
{
    cout<<"ERROR: "<<msg<<endl;
}
//DISJOINT SET CODE
DisjointSet::DisjointSet(int numVertices)
{
    for(int i = 0; i<numVertices; i++)
    {
        makeSet(i);
    }
}
void DisjointSet::makeSet(Vertex x)
{
    bool exists = false;
    for(Set s : subsets)
    {
        if (s.parent == x)
        {
            exists = true;
        }
    }
    if(!exists)
    {
        //subsets.insert(x, Set{.parent = x});
        subsets.push_back(Set{.parent = x});
        //subsets[x].parent = x;
    }
}
Vertex DisjointSet::findSet(Vertex x)
{
    Vertex & parent = subsets[x].parent;
    if (parent != x)
        parent = findSet(parent);
    return parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y)
{
    Vertex xroot = findSet(x);
    Vertex yroot = findSet(y);
    subsets[yroot].parent = xroot;
}
Graph Graph::sort_edges() const
{
    Graph cpy = *this;
    std::sort(cpy.begin(), cpy.end(), compare_e);
    /*
    for (unsigned int index = 1; index<= cpy.size()-1; index++) {

        Edge currentvalue = cpy[index];
        int position = index;

        while (position>0 && cpy[position-1].weight > currentvalue.weight) {
            cpy[position] = cpy[position-1];
            position--;
        }
        cpy[position] = currentvalue;
    }
    std::sort(cpy.begin(), cpy.end());
    */
    return cpy;
}
VertexList Graph::edges_from(Vertex vertex) const
{
    VertexList edges;
    for(const Edge & e: *this)
    {
        if(e.u == vertex)
        {
            edges.push_back(e.v);
        }
    }
    return edges;

}
EdgeList Kruskals(const Graph& G)
{
    DisjointSet ds {G.numVertices}; //does make set for each vertex
    const Graph& sort_edges = G.sort_edges();
    size_t solution_size = G.numVertices -1;
    EdgeList result;
    for(Edge e : sort_edges)
    {
        Vertex uRoot = ds.findSet(e.u);
        Vertex vRoot = ds.findSet(e.v);
        
        if(uRoot != vRoot)
        {
            ds.unionSets(uRoot, vRoot);
            result.push_back(e);
            if(result.size() >= solution_size) break;
        }
    }
    return result;
    
}
int sum_weights(EdgeList const& L)
{
    int total = 0;
    for (Edge x : L)
    {
        total +=x.weight;
    }
    return total;
}
void file_to_graph(string filename, Graph & G)
{
    ifstream in(filename);
    in>>G;

}
VertexList dfs(const Graph& graph, Vertex startVertex)
{
    VertexList result;
    vector<bool> visited(graph.size(), false);
    stack<Vertex> stk;
    visited[startVertex] = true;
    stk.push(startVertex);
    while (!stk.empty()) {
        Vertex vertex = stk.top();
        stk.pop();
        result.push_back(vertex);
            for (Vertex v : graph.edges_from(vertex))
                if (!visited[v]) {
                    visited[v] = true;
                    stk.push(v);
                }
    }
    return result;
}
VertexList bfs(const Graph& graph, Vertex startVertex)
{
    VertexList  result;
    vector<bool> visited(graph.size(), false);
    queue<Vertex> queue;
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        Vertex vertex = queue.front();
        queue.pop();
        result.push_back(vertex);
        for (Vertex v : graph.edges_from(vertex))
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
    }
    return result;
}
string get_arg(int argc, char *argv[], string def)
{
    if (argc == 2)
        return string(argv[1]);
    else
        return def;
}