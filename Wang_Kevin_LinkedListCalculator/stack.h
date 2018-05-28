#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define arraySize 20

struct NODE{ //for the linked list
    float num;
    NODE *next;
};

class Stack {
    protected:
        //first value in the list
        NODE *head;
        //to keep track of how many numbers are in the list
        int top;
    public:
        //constructor
        Stack();
        //deletes first number and returns it
        float pop();
        //pushes inputed number into list
        void push(float n);
        //deletes all contents of list
        void eraseAll();
        //returns the first number in list
        float peek();
        //prints out whole list to console
        void printStack();
        //returns th amount of numbers in list
        int returnTopIndex();
        //destructor
        ~Stack();
};



#endif // STACK_H_INCLUDED

