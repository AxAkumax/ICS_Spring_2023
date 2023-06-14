#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    /*
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.resize(G.size(), -1);
    distances[source] = 0;
    previous[source] = -1; //undefined
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> minHeap;
    minHeap.push({source, 0});
    while(!minHeap.empty())
    {
        const int& u = minHeap.top().first;
        minHeap.pop();

        if(visited[u]) 
        {   continue;
        }
        visited[u] = true;
        for(Edge edge: G[u])
        {
            int v= edge.dst;
            int weight = edge.weight;
            if(!visited[v] && (distances[u]+ weight) < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
    */
    int n = G.size();
    vector<int> distances(n, INF);
    vector<bool> visited(n, false);
    previous.resize(G.size(), -1);
    //greater<pair<int, int>>
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({source, 0});
    distances[source] = 0;
    previous[source] = -1; //undefined

    while (!pq.empty())
    {
        pair<int,int> current = pq.top();
        pq.pop();
        int u = current.first;
        if (visited[u])
        {
            continue;
        }
        visited[u] = true;
        for(Edge edge: G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({v, distances[v]});
            }
        }
    }
    for(int i=0; i<previous.size(); i++)
    {
        cout<<"Vertex: "<<i<<" Previous: "<<previous[i]<<endl;
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& /*distances*/,const vector<int>& previous, int destination)
{
    int current = previous[destination];
    stack<int> order;
    order.push(destination);
    while (current != -1)
    {
        order.push(current);
        current = previous[current];
    }
    vector<int> path;
    int length = order.size();
    for (int i=0; i<length; i++)
    {
        path.push_back(order.top());
        order.pop();
    }
    return path;

}
void file_to_graph(string filename, Graph & G){
     ifstream in(filename);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    in >> G;
    in.close();
}
string get_arg(int argc, char *argv[], string def)
{
    if (argc == 2)
        return string(argv[1]);
    else
        return def;
}
void print_path(const vector<int>& v, int total)
{
    for(int i: v){
        cout<<i<<" ";
    }
    cout<<"\n"<<"Total cost is "<<total<<endl;;
}
