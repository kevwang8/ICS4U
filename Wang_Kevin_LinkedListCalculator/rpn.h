#ifndef RPN_H_INCLUDED
#define RPN_H_INCLUDED
#include "stack.h"

class Rpn : public Stack {
  public:
      //constructor
      Rpn();
      //adding
      void add();
      //subtracting
      void subtract();
      //dividing
      void divide();
      //multiplying
      void multiply();
      //exponents
      void exponent();
      //square roots
      void squareRoot();
        //tangent in degrees
      void tangent();
      //sine in degrees
      void sine();
      //cosine in degrees
      void cosine();
      //destructor
      ~Rpn();
};

#endif // RPN_H_INCLUDED



