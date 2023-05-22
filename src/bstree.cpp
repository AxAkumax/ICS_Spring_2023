#include "bstree.h"
#include "bst.h"

Node * BSTree::insert_node(Node * t, string key)
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
            }
            v = v->left;
        }
        else if ( key  >  v->key ){
            if ( v->right == nullptr )
            {
                v->right = new Node(key, nullptr, nullptr);
            }
            v = v->right;
        }
    }
    return t;
}
Node * BSTree::find_node(Node * t, string key)
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
Node * BSTree::left_most(Node * t)
{
    if(t != nullptr)
    {
        Node* v = t;
        while(v->left)
        {
            v = v->left;
        }
        return v;
    }
    return nullptr;

}
Node *  BSTree::delete_node(Node * t, string key)
{
    if (!t)
    {
        return t;
    } 
    if (key < t->key)
        t->left = delete_node(t->left, key);
    else if (key > t->key)
        t->right = delete_node(t->right, key);
    else { // delete node t
        // Case 1: Node has one or no child
        if (t->left == nullptr || t->right == nullptr) {
            Node * child = t->left ? t->left : t->right;
            // No child case
            if (child == nullptr) {
                child = t;
                t = nullptr;
            } else { // One child case
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
void BSTree::delete_tree(Node * t)
{
    if(t != nullptr)
    {
        delete_tree(t->left);
        delete_tree(t->right);
        delete t;
    }
}
int BSTree::compute_height(Node * t)
{
    if(t != nullptr)
    {
        return 1 + max(compute_height(t->left), compute_height(t->right));
    }
    return 0;
}
BSTree::BSTree() : BST("BSTree") {}
void BSTree::insert(const string & key)
{
    this->root = insert_node(this->root, key);
    this->count += 1;
}
bool BSTree::find(const string & key) const
{
    return find_node(this->root, key) != nullptr;
}
void BSTree::remove(const string & key)
{
    this->root = delete_node(this->root, key);
    this->count--;
}
bool BSTree::is_empty() const
{
    return this->root == nullptr;
}
int BSTree::get_height() const
{
    return compute_height(this->root);
}
BSTree::~BSTree()
{
    delete_tree(this->root);
}