#include <iostream>
#include "fraction.h"
#include "stack.h"
#include "Dictionary.h"

using namespace std;

Stack <Input> numStack;
Stack <char> opStack;
Dictionary variables;

void evaluate (string s);
void operation ();
bool precedence (char, char);
bool isOperator (char x);

int main() {
    string input;
    do {
        cout << "\nPlease input an expression example: x - 5 * ( variable = 3 ) or \"quit\" to quit\n";
        getline(cin, input);
        if (input != "quit") {
            cout << "The expression evaluates to: ";
            evaluate(input);
        }
    }while (input != "quit");
    return 0;
}

bool isOperator (char x) {
    if (x == '+' || x == '-' || x == '=' || x == '*' || x == '/') {
        return true;
    }
    return false;
}

bool precedence (char a, char b) {
    if (a == '*' || a == '/') {
        return true;
    }else if (a == '+' || a == '-') {
        if (b == '*' || b == '/')
            return false;
        else
            return true;
    }
    return false;
}

void operation () {
    char op = opStack.pop();
    Input right = numStack.pop();
    Input left = numStack.pop();
    Input answer;

    if (!left.name.empty()) {
        if (variables.contain(left.name)) {
            left.value = variables.search(left.name);
        }
    }
    if (!right.name.empty()) {
        if (variables.contain(right.name)) {
            right.value = variables.search(right.name);
        }
    }

    if (op == '=') {
        if (!left.name.empty()) {
            variables.add(left.name, right.value);
            numStack.push(right);
        }else {
            variables.add(right.name, left.value);
            numStack.push(left);
        }
    }else if (op == '*') {
        answer.value = left.value * right.value;
        numStack.push(answer);
    }else if (op == '/') {
        answer.value = left.value / right.value;
        numStack.push(answer);
    }else if (op == '+') {
        answer.value = left.value + right.value;
        numStack.push(answer);
    }else if (op == '-') {
        answer.value = left.value - right.value;
        numStack.push(answer);
    }
}


void evaluate (string s) {
    numStack.clear();
    opStack.clear();
    opStack.push('$');
    Input x;
    string input;
    int first = 0;

    while (first < s.length()) {
        if (isdigit(s[first])) {
            x.name = "";
            x.value = 0;
            while (isdigit(s[first])) {
                x.value = x.value * 10 + s[first] - '0';
                first++;
            }
            numStack.push(x);
        }else if (isalpha(s[first]) || s[first] == '_'){
            x.name = "";
            x.value = 0;
            while (isalnum(s[first]) || s[first] == '_') {
                x.name.push_back(s[first]);
                first++;
            }
            numStack.push(x);
        }else if (s[first] == '(') {
            opStack.push(s[first]);
            first++;
        }else if (s[first] == ')') {
            while (opStack.peek() != '(') {
                operation();
            }
            opStack.pop();
            first++;
        }else if (isOperator(s[first]) ){
            while (precedence(opStack.peek(), s[first])) {
                operation();
            }
            opStack.push(s[first]);
            first++;
        }else
            first++;
    }
    while (opStack.peek() != '$') {
        operation();
    }
    cout << numStack.pop().value << endl;
}