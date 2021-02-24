//
// stacks implementation using arrays along with 
//  infix to postfix coversion of an expression using stacks
//	balanced parenthesis check 
//	solving postfix expression 
// 

#include <iostream>
using namespace std;
#include <string.h>
#include <cmath>

#define MAXSIZE 50
template <typename T>

class Stack{
public:
    int top;

public:
    T container[MAXSIZE];

    Stack(){ //constructor
        top = -1;
    }

    bool IsEmpty(){ //to check if stack is empty
        if(top==-1){
            return true;
        }
        else{
            return false;
        }
    }

    bool IsFull(){ //to check if stack is full
        if(top==MAXSIZE-1){
            return true;
        }
        else{
            return false;
        }
    }

    void Push(T x){ //push element on top of stack
        if(IsFull()){
            cout<<"Stack overflow, cant enter more"<<endl;
        }
        else{
            cout<<"element pushed"<<endl;
            container[++top]=x;
        }
    }

    T Pop(){ //remove element from top
        if(IsEmpty()){
            cout<<"CAnt POP element, as no ones there, STACK UNDERFLOW"<<endl;
        }
        else{
            cout<<"element removed"<<endl;
            return (container[top--]);
        }
    }

    T Peek(){ //see the top element without removing it
        if(IsEmpty()){
            cout<<"NONE at top,cant peek "<<endl;
        }
        else{
            cout<<"stalking top element"<<endl;
            return (container[top]);
        }
    }


    bool BalancedParenthesis(string sentence, Stack box) {
        char topCh;
        int valid = 1;

        for (int i = 0; i < sentence.length(); i++) {
            cout << "loop: " << i << endl;
            if (sentence[i] == '(' || sentence[i] == '[' || sentence[i] == '{') {
                box.Push(sentence[i]);
            } else {
                if (sentence[i] == '}' || sentence[i] == ')' || sentence[i] == ']') {
                    topCh = box.Peek();

                    switch (sentence[i]) {

                        case ')': {
                            if (topCh == '{' || topCh == '[') {
                                valid = 0;
                                break;
                            }
                            box.Pop();
                        }
                        case '}': {
                            if (topCh == '(' || topCh == '[') {
                                valid = 0;
                                break;
                            }
                            box.Pop();
                        }

                        case ']': {
                            if (topCh == '{' || topCh == '(') {
                                valid = 0;
                                break;
                            }
                            box.Pop();
                        }
                    }

                }
            }
        }
        if(box.IsEmpty()){
            valid=1;
        }

        if(valid==1){
            return true;
            //cout<<"EXpression is valid, enjoi.."<<endl;
        }else{
            return false;
            //cout<<"EXpression not valid, CORRECT IT!!!"<<endl;
        }
    }




};
int precedence(char ch){ //helper for infinixtopostfix fucntion
    if(ch=='^'){
        return 3;
    }
    else if(ch=='*'||ch=='/'){
        return 2;
    }
    else if(ch=='+'||ch=='-'){
        return 1;
    }
    else{
        return -1;
    }
}

string InFixToPostFix(string expression){
    Stack<char> box;
    box.Push('F');
    int len = expression.length();
    string postFixExpression;

    for(int i=0;i<expression.length();i++){
        if(expression[i]>=48&&expression[i]<=57){
            cout<<"number added in postfix string"<<endl;
            postFixExpression+=expression[i];
        }
        else if(expression[i]=='('){
            box.Push('(');
        }
        else if(expression[i]==')'){
            while(box.Peek()!='('){
                char gucci = box.Pop();
                postFixExpression+=gucci;
            }
            box.Pop();
        }
        else if(expression[i]=='{'){
            box.Push('{');
        }
        else if(expression[i]=='}'){
            while(box.Peek()!='{'){
                char gucci = box.Pop();
                postFixExpression+=gucci;
            }
            box.Pop();
        }
        else if(expression[i]=='['){
            box.Push('[');
        }
        else if(expression[i]==']'){
            while(box.Peek()!='['){
                char gucci = box.Pop();
                postFixExpression+=gucci;
            }
            box.Pop();
        }
        else{
            //postFixExpression+=' ';
            while(box.Peek()!='F'&&precedence(expression[i])<=precedence(box.Peek())){
                char chTopStack = box.Pop();
                //box.Pop();

                postFixExpression+=chTopStack;
                //postFixExpression+=' ';

            }
            postFixExpression+=' ';
            cout<<"pushing operator in stack"<<endl;
            box.Push(expression[i]);
            //postFixExpression+=' ';
        }
        cout<<postFixExpression<<endl;

    }
    while(box.Peek()!='F'){
        char chTopStack = box.Pop();

        postFixExpression+=chTopStack;

    }
    return postFixExpression;
}

int PostFixCalculation(string postFixExpression){
    int len=postFixExpression.length();
    Stack<int> box;
    string number;
    int strTonum;
    int result;
    int op1,op2;
    for(int i=0;i<len;i++){
        if(isdigit(postFixExpression[i])){
            number+=postFixExpression[i];
            if(!isdigit(postFixExpression[i+1])){
                strTonum = stoi(number);
                box.Push(strTonum);
                number="";
            }

        }
        else if(postFixExpression[i]!=' '){
            op2=box.Pop();
            op1=box.Pop();
            switch (postFixExpression[i]) {
                case '^':
                    result = pow(op1,op2);
                    box.Push(result);
                    break;
                case '*':
                    result = op1*op2;
                    box.Push(result);
                    break;
                case '/':
                    result = op1/op2;
                    box.Push(result);
                    break;
                case '+':
                    result = op1+op2;
                    box.Push(result);
                    break;
                case '-':
                    result = op1-op2;
                    box.Push(result);
                    break;
            }
        }
    }
    return box.Pop();
}


int main(void){
    Stack<char> ss;
    string expression;
    cout<<"Enter your string: ";
    getline(cin, expression);
    cout<<"you entered "<<expression<<endl;
    //ss.BalancedParenthesis(expression,ss);
    string postF = InFixToPostFix(expression);
    cout << postF<< endl ;
    int postFixAnswer = PostFixCalculation(postF);

    cout << postFixAnswer<< endl ;

}