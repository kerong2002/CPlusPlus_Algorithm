//2023/04/01 kerong
/*
   Data_Structure : Infix
    Time complexity: O(n)
   Space complexity: O(n)
*/
#include <iostream>
#include <stack>
#include <cctype>
#include <cstring>

using namespace std;

int precedence(char op){
    if(op == '+' || op == '-'){
        return 1;
    }
    else if(op == '*' || op == '/'){
        return 2;
    }
    else{
        return 0;
    }
}

int Postfix_Calculate(string postfix){
    stack<int> s;
    for(int x=0;x<postfix.size();x++){
        if(isdigit(postfix[x])){
            int check_num = x;
            string int_number = "";
            int_number += postfix[check_num];
            while(isdigit(postfix[++check_num])){
                int_number += postfix[check_num];
            }

            x += check_num - x - 1;
            s.push(stoi(int_number));
        }
        else if(postfix[x]==' '){
            continue;
        }
        else{
            int top2 = s.top();
            s.pop();
            int top1 = s.top();
            s.pop();
            int ans = 0;
            switch(postfix[x]){
                case '+':
                    ans = top1 + top2;
                    break;
                case '-':
                    ans = top1 - top2;
                    break;
                case '*':
                    ans = top1 * top2;
                    break;
                case '/':
                    ans = top1 / top2;
                    break;
            }
            s.push(ans);
        }
    }
    return s.top();
}

string Infix_to_Postfix(string infix){
    stack<char> operator_c;
    string postfix = "";
    for(int x=0;x<infix.size();x++){
        char current_op = infix[x];
        if(isdigit(current_op)){
            int check_number = x;
            while(isdigit( infix[check_number])){
                postfix += infix[check_number];
                check_number++;
            }
            x +=  check_number - x - 1;
            postfix += " ";
        }
        else if(current_op==' '){
            continue;
        }
        else{
            while(!operator_c.empty() && precedence(current_op) <= precedence(operator_c.top())){
                postfix += operator_c.top();
                postfix += " ";
                operator_c.pop();
            }
            operator_c.push(current_op);
        }
    }
    while(!operator_c.empty()){
        postfix += operator_c.top();
        operator_c.pop();
    }
    return postfix;
}

int main(){
    string infix = "1*2-3/4+5*6-7*8+9/10";
    string postfix = Infix_to_Postfix(infix);
    cout << postfix << endl;
    cout << Postfix_Calculate(postfix) << endl;
    return 0;
}
