#include "hasher.h"
#include "hashtable.h"
#include "stats.cpp"
//#include "stats.h" for submission
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//LISTNODE FUNCTIONS
ListNode * ListNode::find(string key, ListNode * L)
{
    ListNode * top = L;
    while (top!=nullptr){
        if(top->data == key){
            return top;
        }
        top = top->next;
    }
    return nullptr;
}
ListNode * ListNode::insert(string key, ListNode * L)
{
    //insert at the front of the list
    if(L==nullptr)
    {
        L = new ListNode(key, nullptr);
    }
    else
    {
        ListNode* new_node = new ListNode(key, L);
        L = new_node;
    }
    return L;
}
ListNode * ListNode::remove(string key, ListNode * L)
{
    ListNode* next_node = L->next; //next_node
    ListNode* current = L; //current
    //current = L;
    //next_node = L->next;
    ListNode* removed = find(key, L);
    if (removed!=nullptr){
        //if value is the first node
        if(current->data == key){
            L = next_node;
            delete current;
        }
        else{
            while(next_node->data != key){
                next_node = next_node->next;
                current = current->next;
            }
            //now check for last node
            if (next_node->next == NULL){
                current->next = NULL;
                delete next_node;
            }
            //internal node
            else {
                current->next = next_node->next;
                delete next_node;
            }
        }
    }
    return L;
}
void ListNode::print(ostream & out, ListNode * L)
{
    ListNode * top = L;
    while (top != nullptr){
        out<<top->data<<" ";
        top = top->next;
    }
}
int ListNode::length(ListNode * L)
{
    int length = 0;
    ListNode *top = L;
    while (top != nullptr){
        ++length;
        top = top->next;
    }
    return length;
}
void ListNode::delete_list(ListNode * L)
{
    //delete list
    ListNode * top = L;
    while(top != nullptr){
        ListNode* p = top;
        top = top->next;
        delete p;
    }
    delete top;
}
//HASHTABLE FUNCTIONS
void HashTable::insert( const string & word)
{
    int index = hasher.hash(word, capacity);
    buf[index] = ListNode::insert(word, buf[index]);
}
bool HashTable::find( const string & word)
{
    int index = hasher.hash(word, capacity);
    ListNode* location = ListNode::find(word, buf[index]);
    if (location == nullptr){
        return false;
    }
    return true;
}
void HashTable::remove( const string & word)
{
    int index = hasher.hash(word, capacity);
    buf[index] = ListNode::remove(word, buf[index]);
}
bool HashTable::is_empty()
{
    //check each of the linked lists to make sure it is nullptr
    for (size_t i=0; i<capacity; ++i)
    {
        if(buf[i] != nullptr)
        {
            return false;
        }
    }
    return true;
}
bool HashTable::is_full()
{
    return false;
}
void HashTable::print(ostream & out)
{
    for (size_t i=0; i<capacity; ++i)
    {
       ListNode::print(out, buf[i]);
    }
}
HashTable::~HashTable()
{
    for (size_t i=0; i<capacity; ++i)
    {
       ListNode::delete_list(buf[i]);
    }
    delete [] buf;
}
size_t HashTable::number_of_entries()
{
    int entries = 0;
    for (size_t i=0; i<capacity; ++i)
    {
       entries = entries + ListNode::length(buf[i]);
    }
    return entries;
}
size_t HashTable::number_of_chains()
{
    return capacity;
}
void HashTable::get_chain_lengths(vector<int> & v)
{
    for(size_t i=0; i<capacity; ++i)
    {
        v.push_back(ListNode::length(buf[i]));
    }
}

//NON-CLASS FUNCTIONS
void error(string word, string msg)
{
    //print error message
    cout<<"ERROR: "<<word<<" "<<msg<<endl;
}
void insert_all_words(string file_name, HashTable & L)
{
    //insert all words
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (std::string string_word; (in >> string_word) && limit > 0 ; --limit){
        L.insert(string_word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<< "\t\tI = " << eTime << endl;
}
void find_all_words(string file_name, HashTable & L)
{
    //find all words
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (std::string string_word; (in >> string_word) && limit > 0 ; --limit){
        L.find(string_word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<< "\t\tF = " << eTime << endl;

}
void remove_all_words(string file_name, HashTable & L)
{
    //remove all words
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (std::string string_word; (in >> string_word) && limit > 0 ; --limit){
        L.remove(string_word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<< "\t\tR = " << eTime << endl;

}
void measure_hashtable(string file_name, HashTable & L)
{
    cout << L.get_name() << endl;
    insert_all_words(file_name, L);

    vector<int> chain_lengths;
    L.get_chain_lengths(chain_lengths);
    Stats stats(L.get_name(), chain_lengths);
    stats.print(cout);

    find_all_words(file_name, L);
    remove_all_words(file_name, L);
    if (!L.is_empty()){
        error(L.get_name(), "is not empty");
    }
}
void measure_hashtables(string input_file)
{
    Hasher *H [] = { 
        new ChatGPTHasher{}, 
        new GoodrichHasher{},
        new MultHasher{},
        new PreissHasher{},
        new PJWHasher{},
        new STLHasher{},
        new SumHasher{},
        new Weiss1Hasher{},
        new Weiss2Hasher{},
        new WeissHasher{},
        new MyHasher{},
    };
    int S[] = {
        //10000,
       // 1000
        //100
        //10
        1
    };
    for(auto size : S)
    {
        for(auto h: H)
        {
            HashTable ht(*h, size);
            measure_hashtable(input_file, ht);
        }
    }
}