#include "avltree.h"
#include "bst.h"
#include <iostream>
#include <fstream>
using namespace std;

int AVLTree::get_height(Node * node)
{
    if(node == nullptr)
        return 0;
    return node->height;

}
int AVLTree::get_balance(Node * node)
{
    if(node == nullptr)
    {
        return 0;
    }
    return node ? get_height(node->left) - get_height(node->right) : 0;
}
void AVLTree::set_height(Node * node)
{
    if(node!=nullptr)
    {
        node->height = 1 + max(compute_height(node->left), compute_height(node->right));
    }
    else
    {
        node->height = 0;
    }
}
Node * AVLTree::right_rotate(Node * y)
{
     Node * x = y->left;
    Node * T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    set_height(y);
    set_height(x);
 
    // Return new root
    return x;
}
Node * AVLTree::left_rotate(Node * x)
{
    Node * y = x -> right;
    Node * T = y -> left;
    y -> left = x;
    x -> right = y;
    set_height(x);                // Update heights
    set_height(y);
    return y;   
}
Node * AVLTree::rebalance(Node * t)
{
    set_height(t);
    int balance = get_balance(t);
    if (t != nullptr)
    {
        if ( balance > 1 ) 
        {
            if ( get_balance(t->left) < 0 )
            {
                t->left = left_rotate(t->left);
            }
            return right_rotate(t);
       } 
        else if ( balance < -1 ) 
        {
            if ( get_balance(t->right ) > 0)
            {
                t->right = right_rotate(t->right);
            }
            return left_rotate(t);
        }
    }
    return t;
}
int AVLTree::compute_height(Node * t)
{
    if(t != nullptr)
    {
        return 1 + max(compute_height(t->left), compute_height(t->right));
    }
    return 0;
}
Node * AVLTree::insert_node(Node * t, string key)
{
    if ( t == nullptr )
    {
        t = new Node(key, nullptr, nullptr);  
    }
    Node * v = t;
    while ( v->key  !=  key)
    {
         if ( key  <  v->key){
            if ( v->left == nullptr )
            {
                v->left = new Node(key, nullptr, nullptr);
                v->left = rebalance(v->left);
            }
            v = v->left;
        }
        else if ( key  >  v->key ){
            if ( v->right == nullptr )
            {
                v->right = new Node(key, nullptr, nullptr);
                v->right = rebalance(v->right);
            }
            v = v->right;
        }
    }
    v = rebalance(v);
    return t;
}
Node * AVLTree::find_node(Node * t, string key)
{
    if(t != nullptr)
    {
        if(t->key > key)
        {
            return find_node(t->left, key);
        }
        else if(t->key < key)
        {
            return find_node(t->right, key);
        }
        else
        {
            return t;
        }
    }
  return nullptr;

}
Node * AVLTree::delete_node(Node * t, string key)
{
    if (t == nullptr)
    {
        return t;
    } 
    if (key < t->key)
    {
        t->left = delete_node(t->left, key);
    }
    else if (key > t->key)
    {
        t->right = delete_node(t->right, key);
    }
    else { // delete node t
        // Case 1: Node has one or no child
        if (t->left == nullptr || t->right == nullptr) {
            Node * child = t->left ? t->left : t->right;
            // No child case
            if (child == nullptr) {
                child = t;
                t = nullptr;
            } 
            else 
            { // One child case
                *t = *child; // copy data up from child
            }
            delete child;
        }
        else {
            Node * succ = left_most(t->right);
            swap(t->key, succ->key);
            t->right = delete_node(t->right, key);
        }
    }
    return t;
}
void AVLTree::delete_tree(Node * t)
{
    if(t != nullptr)
    {
        delete_tree(t->left);
        delete_tree(t->right);
        delete t;
    }
}
Node * AVLTree::left_most(Node * t)
{
    if(t != nullptr)
    {
        while(t->left)
        {
            t = t->left;
        }
        return t;
    }
    return nullptr;
}

AVLTree::AVLTree(): BST("AVLTree") {}

void AVLTree::insert(const string & key)
{
    this->root = insert_node(this->root, key);
    //this->root = rebalance(this->root);
    this->count++;

}
bool AVLTree::find(const string & key) const
{
    return find_node(this->root, key) != nullptr;
}
void AVLTree::remove(const string & key)
{
    this->root = delete_node(this->root, key);
    if(!is_empty())
        this->root = rebalance(this->root);
        this->count--;
}
bool AVLTree::is_empty() const
{
    return this->root == nullptr;
}
int AVLTree::get_height() const
{
    return get_height(this->root);
}
AVLTree::~AVLTree()
{
    delete_tree(this->root);
}