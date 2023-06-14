#include "dijkstras.h"
#include "ladder.h"
#include <iostream>
#include <set>
int main(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "small.txt");
    Graph G;
    file_to_graph(filename, G);
    vector<int> prev;
    vector<int>distances = dijkstra_shortest_path(G, 0, prev);
    vector<int> path = extract_shortest_path(distances, prev, 2);
    print_path(path, 6);

    set<string> words;
    load_words(words, "words.txt");
    vector<string> ladder = generate_word_ladder("car", "cheat", words);
    print_word_ladder(ladder);
    ladder = generate_word_ladder("head", "tail", words);
    print_word_ladder(ladder);


}
