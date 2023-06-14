#include "dijkstras.h"
#include <iostream>
#include <vector>

void test_dijkstras(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "small.txt");
    Graph G;
    file_to_graph(filename, G);
    vector<int> prev;
    vector<int>distances = dijkstra_shortest_path(G, 0, prev);
    cout<<"Dijkstra's Path: ";
    print_path(distances, 6);
}