#include <iostream>
#include "stack.h"
#define arraySize 20


Stack::Stack() { //constructor for initialization
   top = -1;
    for (int i = 0; i < arraySize; i++)
        nums[i] = 0;
}

void Stack::push(float n) { //pushes in number inputted
    if (top == arraySize-1){ //tells user if stack is full
        std::cout << "The stack is full" << std::endl;
    }else{
        top++;
        nums[top] = n;
    }
}

float Stack::pop() { //pops out top number and returns it
    float n;

    if (top == -1) { //error message for more numbers
       std::cout << "More numbers are needed in stack" << std::endl;
    }
    else{
        n = nums[top];
        top--;
        return n;
    }
}

void Stack::Delete() { //decreases top by one which seems as though the top number was deleted
    top--;
}

void Stack::eraseAll(){ //reset top so that the stack seems empty
    top = -1;
    for (int i = 0; i < arraySize; i++){
        nums[i] = 0;
    }
    std::cout << "Stack Cleared" << std::endl;
}


float Stack::peek() { //returns top number in stack
        return nums[top];
}

int Stack::returnTopIndex(){ //returns the index of top
    return top;
}

void Stack::printStack(){ //prints out the stack to the console

    for (int j = 0; j <= top; j++)
        std::cout << nums[j] << ", ";
}

Stack::~Stack(){ //destructor

}
