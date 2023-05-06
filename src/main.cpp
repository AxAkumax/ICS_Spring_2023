#include "holder.cpp"
#include <iostream>
#include <string>

using namespace std;

void linked_queue()
{
    cout<<"----LINKED QUEUE CHECK----"<<endl;
    LinkedQueue lq;
    lq.insert("A");
    lq.insert("B");
    lq.insert("C");
    lq.insert("D");
    cout<<"\tCheck for empty: "<<lq.is_empty()<<endl;
    cout<<lq<<endl;
    lq.remove();
    cout<<"\tCheck for remove: "<<lq<<endl;
    cout<<"\tCheck for next value: "<<lq.peek()<<endl;
    cout<<"\tCheck for full: "<<lq.is_full()<<endl;
    lq.remove();
    lq.remove();
    lq.remove();
    cout<<"\tCheck if empty: "<<lq.is_empty()<<endl;
    cout<<lq<<endl;
}
void array_queue()
{
    cout<<"----ARRAY QUEUE CHECK-----"<<endl;
    ArrayQueue aq;
    aq.insert("A");
    aq.insert("B");
    aq.insert("C");
    aq.insert("D");
    cout<<"\tCheck for empty: "<<aq.is_empty()<<endl;
    cout<<aq<<endl;
    aq.remove();
    cout<<"\tCheck for remove: "<<aq<<endl;
    cout<<"\tCheck for next value: "<<aq.peek()<<endl;
    cout<<"\tCheck for full: "<<aq.is_full()<<endl;
    aq.remove();
    aq.remove();
    aq.remove();
    cout<<"\tCheck if empty: "<<aq.is_empty()<<endl;
    cout<<aq<<endl;
}
void linked_stack()
{
    cout<<"----LINKED STACK CHECK-----"<<endl;
    LinkedStack ls;
    ls.insert("A");
    ls.insert("B");
    ls.insert("C");
    ls.insert("D");
    cout<<"\tCheck for empty: "<<ls.is_empty()<<endl;
    cout<<ls<<endl;
    ls.remove();
    cout<<"\tCheck for remove: "<<ls<<endl;
    cout<<"\tCheck for next value: "<<ls.peek()<<endl;   
    cout<<"\tCheck for full: "<<ls.is_full()<<endl;
    ls.remove();
    ls.remove();
    ls.remove();
    cout<<"\tCheck if empty: "<<ls.is_empty()<<endl;
    cout<<ls<<endl;
}
void array_stack()
{
    cout<<"----ARRAY STACK CHECK-----"<<endl;
    ArrayStack as;
    as.insert("A");
    as.insert("B");
    as.insert("C");
    as.insert("D");
    cout<<"\tCheck for empty: "<<as.is_empty()<<endl;
    cout<<as<<endl;
    as.remove();
    cout<<"\tCheck for remove: "<<as<<endl;
    cout<<"\tCheck for next value: "<<as.peek()<<endl;   
    cout<<"\tCheck for full: "<<as.is_full()<<endl;
    as.remove();
    as.remove();
    as.remove();
    cout<<"\tCheck if empty: "<<as.is_empty()<<endl;
    cout<<as<<endl;
}
void sample_test()
{
    ArrayQueue aq;
    aq.insert("a");
    aq.insert(" ");
    aq.insert("a");
    aq.insert("b");

    cout<<"QUEUE: "<<endl;
    cout<<aq<<endl;
    aq.remove();
    cout<<"AFTER REMOVE 1: "<<endl;
    cout<<aq<<endl;
    aq.remove();
    cout<<"AFTER REMOVE 2: "<<endl;
    cout<<aq<<endl;
    aq.remove();
    cout<<"AFTER REMOVE 3: "<<endl;
    cout<<aq<<endl;
    aq.remove();
    cout<<"AFTER REMOVE 4: "<<endl;
    cout<<aq<<endl;
    aq.remove();
    cout<<"AFTER REMOVE 5: "<<endl;
    cout<<aq<<endl;
}
int main()
{
    linked_queue();
    cout<<"\n";
    array_queue();
    cout<<"\n";
    linked_stack();
    cout<<"\n";
    array_stack();
    cout<<"\n";
    sample_test();
    cout<<"\n";
    measure_holders("words.txt");
}
