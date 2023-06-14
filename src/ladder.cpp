#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"
#include <cassert>

using namespace std;

void error(string word1, string word2, string msg)
{
    cout << "ERROR: '" << word1 << "' '" << word2 << "' " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    // Find lengths of given strings
    int m = str1.length(), n = str2.length();
 
    // If difference between lengths is more than
    // 1, then strings can't be at one distance
    if (abs(m - n) > 1)
        return false;
 
    int count = 0; // Count of edits
    int i = 0, j = 0;
    while (i < m && j < n)
    {
        // If current characters don't match
        if (str1[i] != str2[j])
        {
            if (count == 1)
                return false;
 
            // If length of one string is
            // more, then only possible edit
            // is to remove a character
            if (m > n)
                i++;
            else if (m< n)
                j++;
            else //Iflengths of both strings is same
            {
                i++;
                j++;
            }
             
            // Increment count of edits
            count++;
        }
 
        else // If current characters match
        {
            i++;
            j++;
        }
    }
      // If last character is extra in any string
    if (i < m || j < n)
        count++;
 
    return count <= d;
}
bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);

}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word != end_word)
    {
        queue<vector<string>>ladder_queue;
        vector<string> x;
        x.push_back(begin_word);
        ladder_queue.push(x);
        set<string> visited;
        visited.insert(begin_word);
        while (!ladder_queue.empty()){
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder[ladder.size()-1];
            for (string word: word_list){
                if (is_adjacent(last_word, word)){
                    if (!visited.contains(word)){
                        visited.insert(word);
                        vector<string> new_ladder(ladder);
                        new_ladder.push_back(word);
                        if (word == end_word){
                            return new_ladder;
                        }
                        ladder_queue.push(new_ladder);
                    }
                }
            }
        }
    }
    vector<string> en;
    return en;
}
void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);
    if (!file) {
        error("", "", "Can't open input file");
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}
void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.size()>0)
    {
        cout<<"Word ladder found: ";
        for(int i =0; i<ladder.size(); i++)
        {
            cout<<ladder[i]<<" ";
        }
        cout<<"\n";
    }
    else
    {
        cout<<"No word ladder found."<<"\n";
    }
}
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
