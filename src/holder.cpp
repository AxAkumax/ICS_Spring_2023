#include "holder.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Timer.h"
using namespace std;

//------------------STACK PRINT OPERATOR-------------------
ostream & operator << (ostream & out, Stack & L){
    //output operator
    L.print(out);
    return out;
}
//----------ARRAY STACK---------- 
ArrayStack::ArrayStack(int cap)
    : Stack("ArrayStack"), capacity(cap), size(0), buf(new string[cap]) {}
void ArrayStack::push(const string & word)
//push an object into the stack
{
    if(!is_full())
   {
     buf[size++] = word;
   }
}
void ArrayStack::pop()
//pop an object from the stack
{
    if(!is_empty())
    {
       --size;
    }
}
string ArrayStack::top()
//get the top value from stack
{
    if(!is_empty())
    {
        return buf[size-1];
    }
    return "";
}
bool ArrayStack::is_empty()
{
    return size<=0;
}
bool ArrayStack::is_full()
{
    return size==capacity;
}
void ArrayStack::print(ostream & out)
{
    for(int i=size-1; i>=0; i--)
    {
        out<<buf[i]<<" ";
    }
}
ArrayStack::~ArrayStack()
{
    delete [] buf;
}
//LIST NODE STRUCT FUNCTIONS
void ListNode::print(ostream & out, ListNode * L)
{
     //printing a linked list
    ListNode * top = L;
    while (top != nullptr){
        out<<top->data<<" ";
        top = top->next;
    }
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
//-------LINKED STACK CLASS FUNCTIONS--------
LinkedStack::LinkedStack(): Stack("LinkedStack"), head(nullptr) {}

void LinkedStack::push(const string & word)
//push value into linked stack
{
    head = new ListNode(word, head);
}
void LinkedStack::pop()
{
    if(!is_empty())
    {
        ListNode *top = head;
        head = head->next;
        delete top;
    }
}
string LinkedStack::top()
{
    if(!is_empty())
    {
        ListNode *p = head;
        string ret = p->data;
        return ret;
  }
  return "";
}
bool LinkedStack::is_empty()
{
    return head==nullptr;
}
bool LinkedStack::is_full()
{
    return false;
}
void LinkedStack::print(ostream & out)
{
    //printing a linked list
    ListNode::print(out, head);
}
LinkedStack::~LinkedStack()
{
    //delete linked list
    ListNode::delete_list(head);
}
//-----------------QUEUE PRINT OPERATOR-----------------------
ostream & operator << (ostream & out, Queue & L)
{
    //output operator
    L.print(out);
    return out;
}
//------------ARRAY QUEUE-------------
ArrayQueue::ArrayQueue(int cap)
	: Queue("ArrayQueue"), capacity(cap+1), front(0), rear(0), buf(new string[cap +1]) {}

void ArrayQueue::enq(const string & word)
//add value to array queue
{
    if(!this->is_full())
    {
        buf[rear] = word; 
        rear = (rear + 1) % capacity;
    }
}
void ArrayQueue::deq()
{
   if(!this->is_empty())
    {
        buf[front] = "";
        front = (front+1) % capacity;
    }
}
string ArrayQueue::next()
//remove value from array queue
{
    if(!this->is_empty())
    {
        string v = buf[front];
        return v;
    }
    return "";
}
bool ArrayQueue::is_empty()
{
    return front == rear;
}
bool ArrayQueue::is_full()
{
    return ((rear+1) % capacity) == front ;
}
void ArrayQueue::print(ostream & out)
{

    for(int i= front; i!=rear; i = (i+1)%capacity)
    {
        out<<buf[i]<<" ";
    }
    out<<buf[rear];
}
ArrayQueue::~ArrayQueue(){
    delete [] buf;
}
//------------LINKED LIST QUEUE-------------
LinkedQueue::LinkedQueue()
    : Queue("LinkedQueue"), head(nullptr), tail(nullptr) {}

void LinkedQueue::enq(const string & word)
{
    ListNode* newNode = new ListNode(word, nullptr);
    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
        //head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}
void LinkedQueue::deq()
//remove a value from queue
{
    if(!is_empty())
    {
        ListNode *top = head;
        head = head->next;
        delete top;
    }
}
string LinkedQueue::next()
//return the value from next in queue
{
    if(!is_empty())
    {
        return head->data;
    }
    return "";
}
bool LinkedQueue::is_empty()
{
    return head == nullptr;
}
bool LinkedQueue::is_full()
{
    return false;
}
void LinkedQueue::print(ostream & out)
{
    ListNode::print(out, head);
}
LinkedQueue::~LinkedQueue()
{
    ListNode::delete_list(head);
}
//NON CLASS METHODS
void error(string word, string msg)
{
     //print error message
    cout<<"ERROR: "<<word<<" "<<msg<<endl;
}
void insert_all_words(int k, string file_name, Holder & L)
//calculate insert_all_words
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
void remove_all_words(int k, string file_name, Holder & L)
//remove the words
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS/10;
    t.start();
    for (std::string string_word; (in >> string_word) && limit > 0 ; --limit){
        L.remove();
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<< "\t\tR = " << eTime << endl;
}
void measure_holder(string file_name, Holder & L)
{
    cout << L.name << endl;
    for(int K = 1; K<=10; ++K){
        //go through 1/10 of the section till 1
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if (!L.is_empty()){
            error(L.name, "is not empty");
        }
    }
}
void measure_holders(string input_file){
    //array
    ArrayQueue AQ;
    measure_holder(input_file, AQ);
    ArrayStack AS;
    measure_holder(input_file, AS);
    //Linked list
    LinkedQueue LQ;
    measure_holder(input_file, LQ);
    LinkedStack LS;
    measure_holder(input_file, LS);
}