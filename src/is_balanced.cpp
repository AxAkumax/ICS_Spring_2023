#include "is_balanced.h"
#include <iostream>
#include <stack>
#include <string>
using namespace std;

void error(string msg, char c)
{
    cout<<"ERROR: "<<c<<" "<<msg<<endl;
}
bool is_balanced(string s)
{
    stack<char> brackets;
    for(int i = 0; i<s.length(); i++)
    {
        if(brackets.empty())
        {
            //if no bracket exists, push another one
            brackets.push(s[i]);
        }
        else if( brackets.top() =='(' && s[i] == ')' || brackets.top() =='[' && s[i] == ']'
                || brackets.top() =='{' && s[i] == '}'||brackets.top() =='<' && s[i] == '>')
        {
            brackets.pop();
        }
        else
        {
            //if there is another bracket, keep adding on
            brackets.push(s[i]);
        }
    }
    return brackets.empty();
}
void test_is_balanced()
{
    string string_1 = "({(())})((([({})])))(((((<>([{()}])(<>))))))()";
    bool str_1 = true;
    bool str_1_result = is_balanced(string_1);

    string string_2 = "“({(<>)})((([({})])))(((((()([{()}])(())))))”";
    bool str_2 = false;
    bool str_2_result = is_balanced(string_2);

    string string_3 = "({(<>)})((([({})])))((((([]([{<>}])(()))))))()])";
    bool str_3 = false;
    bool str_3_result = is_balanced(string_3);

    if(str_1 == str_1_result)
    {
        cout<<"STRING 1 TEST IS CORRECT"<<endl;
    }
    else
    {
        cout<<"STRING 1 TEST IS INCORRECT"<<endl;
    }
    if(str_2 == str_2_result)
    {
        cout<<"STRING 2 TEST IS CORRECT"<<endl;
    }
    else
    {
        cout<<"STRING 2 TEST IS INCORRECT"<<endl;
    }
    if(str_3 == str_3_result)
    {
        cout<<"STRING 3 TEST IS CORRECT"<<endl;
    }
    else
    {
        cout<<"STRING 3 TEST IS INCORRECT"<<endl;
    }
}

