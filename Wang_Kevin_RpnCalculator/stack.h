#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define arraySize 20

class Stack {
    protected:
        float nums[arraySize];
        int top;
    public:
        //constructor
        Stack();
        //deletes first number and returns it
        float pop();
        //just deletes first number in list
        void Delete();
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
