#include <iostream>
#include "fraction.h"
#include "stack.h"
#include "Dictionary.h"

using namespace std;

Stack numStack, opStack;
Dictionary variables;

struct Input {
    string x;
    Fraction y;

};

void Evaluate (string s);

int main() {
    variables.add("Abe", 5/1);
    variables.add("Abe", 6/5);
    cout << variables.search("Abe") << endl;
    return 0;
}
/*
void Evaluate (string s) {
    numStack.clear();
    opStack.clear();
    opStack.push('$');
    int first = 0;

    while (first < s.length()) {
        if (s[first] >= '0' || s[first] <= '9') {

        }else if (s[first] == '(') {
            opStack.push('(');
            first++;
        }else if (s[first] == ')') {
            while (opStack.peek() != '(') {
                opStack.pop();
            }
        }
    }
}*/