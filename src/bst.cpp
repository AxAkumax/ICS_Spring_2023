#include "bst.h"
#include "bstree.h"
//#include "bstree.cpp"
#include "avltree.h"
//#include "avltree.cpp"
#include "timer.h"
#include <iostream>
#include <fstream>

void BST::pre_order_print(ostream & out, Node * t)
{
    if(t!=nullptr)
    {
        out << t->key << " ";
        pre_order_print(out, t->left);
        pre_order_print(out, t->right);
    }
}
void BST::in_order_print(ostream & out, Node * t)
{
    if(t!=nullptr)
    {
        in_order_print(out, t->left);
        out << t->key << " ";
        in_order_print(out, t->right);
    }

}
void BST::post_order_print(ostream & out, Node * t)
{
    if(t!=nullptr)
    {
        post_order_print(out, t->left);
        post_order_print(out, t->right);
        out << t->key << " ";
    }
}
ostream & operator << (ostream & out, BST & L)
{
    //output operator
    L.print(out);
    return out;
}
void error(string word, string msg)
{
    //print error message
    cout<<"ERROR: "<<word<<" "<<msg<<endl;
}
void insert_all_words(int k, string file_name, BST & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS/10;
    t.start();
    for (std::string string_word; (in >> string_word) && limit > 0 ; --limit){
        L.insert(string_word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<< "\t\tI = " << eTime << endl;
}
void find_all_words(int k, string file_name, BST & L)
{
    //find all words
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS/10;
    t.start();
    for (std::string string_word; (in >> string_word) && limit > 0 ; --limit){
        L.find(string_word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<< "\t\tF = " << eTime << endl;

}
void remove_all_words(int k, string file_name, BST & L)
{
    //remove all words
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS/10;
    t.start();
    for (std::string string_word; (in >> string_word) && limit > 0 ; --limit){
        L.remove(string_word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<< "\t\tR = " << eTime << endl;

}
void measure_BST(string file_name, BST & L)
{
    cout << L.name << endl;
    for(int K = 1; K<=10; ++K){
        //go through 1/10 of the section till 1
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if (!L.is_empty()){
            error(L.name, "is not empty");
        }
    }
}
void measure_BSTs(string input_file)
{
    BSTree bstree;
    measure_BST(input_file, bstree);
    AVLTree avltree;
    measure_BST(input_file, avltree);
}
