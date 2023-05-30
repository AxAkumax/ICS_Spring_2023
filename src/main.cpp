#include "sorter.h"
#include <iostream>
#include <vector>
using namespace std;

void test_QuickSorter()
{
    cout<<"QuickSort: ";
    vector<string> words;
    words.push_back("apple");
    words.push_back("Ant");
    words.push_back("bobby");
    words.push_back("Bab");
    words.push_back("cap");
    words.push_back("cap");
    words.push_back("zombie");
    QuickSorter::quicksort(words, 0, words.size()-1);
    for(string word:words)
    {
        cout<<word<<" ";
    }
    cout<<"\n";
    //Right order: Ant Bab apple bobby cap zombie
}
void test_InsertionSorter()
{
    cout<<"InsertionSort: ";
    vector<string> words;
    words.push_back("apple");
    words.push_back("Ant");
    words.push_back("bobby");
    words.push_back("Bab");
    words.push_back("cap");
    words.push_back("zombie");
    InsertionSorter::insertionsort(words, 0, words.size()-1);
    for(string word:words)
    {
        cout<<word<<" ";
    }
    cout<<"\n";
}
void test_HeapSorter_all()
{
    cout<<"All HeapSort: ";
    vector<string> words;
    words.push_back("apple");
    words.push_back("Ant");
    words.push_back("bobby");
    words.push_back("Bab");
    words.push_back("cap");
    words.push_back("zombie");
    HeapSorter::heapsort(words, 0, words.size()-1);
    for(string word:words)
    {
        cout<<word<<" ";
    }
    cout<<"\n";
}
void test_HeapSorter_varied()
{
    cout<<"Varied HeapSort: ";
    vector<string> words;
    words.push_back("apple");
    words.push_back("Ant");
    words.push_back("bobby");
    words.push_back("Bab");
    words.push_back("cap");
    words.push_back("zombie");
    HeapSorter::heapsort(words, 1, words.size()-1);
    for(string word:words)
    {
        cout<<word<<" ";
    }
    cout<<"\n";
}
int main()
{
    test_QuickSorter();
    test_InsertionSorter();
    test_HeapSorter_all();
    test_HeapSorter_varied();
        //measure_sorters("shortrandom.txt");
    measure_sorters("random.txt");
        //measure_sorters("shortsorted.txt");
    measure_sorters("sorted.txt");
}
