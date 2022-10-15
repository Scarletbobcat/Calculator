#include <cstdint>
#include "fraction.h"

#ifndef _STACK_H
#define _STACK_H

struct Input {
    std::string name;
    Fraction value;
};


const uint32_t
        STACK_SIZE = 16;

template <class Input>

class Stack {
public:
    Stack() {top = 0;};
    ~Stack() = default;

    void clear() { top = 0; }
    bool isEmpty() { return top == 0; }
    uint32_t size() { return top; }

    void push(Input d) {
        if (top == STACK_SIZE)
            throw std::overflow_error("Stack is full");

        // next two lines can be written as data[top++] = d
        data[top] = d;

        top++;
    };

    Input pop() {
        if (top == 0)
            throw std::underflow_error("Stack is empty");

        return data[--top];
    };
    Input peek() {
        if (top == 0)
            throw std::underflow_error("Stack is empty");

        return data[top-1];
    };

private:
    Input
            data[STACK_SIZE];
    uint32_t
            top;
};

#endif
