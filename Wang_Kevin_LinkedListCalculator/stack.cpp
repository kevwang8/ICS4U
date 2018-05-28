#include <iostream>
#include "stack.h"


Stack::Stack() { //constructor for initialization
    top = -1;
    head = nullptr;

}

void Stack::push(float n) {

    NODE *newnode = new NODE; //creates new node for the input
    newnode->num = 0;
    newnode->next = nullptr;

   // if first insert before head
   if (head == nullptr) {
      head = newnode;
      head->num = n;
      top++;
   }
   else{
        newnode->next = head;
        head = newnode; //makes head the new input node
        head->num = n;
        top++; //increase counter
   }
}

float Stack::pop() {
        top--; //decrease counter
        float n;
        n = head->num;
        NODE *temp = head; //repositions head to delete the old head
        head = head->next;
        delete temp;
        return n; //returns the popped number

}

void Stack::eraseAll(){
    top = -1; //makes counter back to empty
    while (head) { //runs loop to delete all contents of list
        NODE *temp = head;
        head = head->next;
        delete temp;
    }
    std::cout << "Stack Cleared" << std::endl;
}


float Stack::peek() {
        return head->num; //returns the first number in list
}

int Stack::returnTopIndex(){
    return top; //returns the counter
}

void Stack::printStack(){ //prints out the contents of the stack onto the console
    for (NODE *temp = head; temp; temp = temp->next)
        std::cout << temp->num << ", ";
}

Stack::~Stack(){ //destructor

}
