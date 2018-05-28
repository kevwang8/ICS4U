#include <iostream>
#include <math.h>
#include "rpn.h"

Rpn::Rpn(){ //constructor
}

void Rpn::add() { //adds first 2 values
    if (top > 0){ //makes sure there are enough values
        float answer = pop() + pop();

        push(answer);

    }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::subtract(){ //subtracts the first 2 values
    if (top > 0){ //makes sure there are enough values
        float n2 = pop();
        float n1 = pop();

        float answer = n1 - n2;
        push(answer);

    }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::divide() { //divides first 2 values
    if (top > 0){ //makes sure there are enough values
        float n2 = pop();
        float n1 = pop();

        if (n2 == 0.0){ //outputs error message if user tries to divide by 0
            std::cout << std::endl;
            std::cout << "Error: Cannot divide by 0!" << std::endl;
            std::cout << std::endl;
            push(n1);
            push(n2);
        }
        else{
            float answer = n1 / n2;
            push(answer);

        }
    }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::multiply() { //multiplies first 2 values
    if (top > 0){ //makes sure there are enough values
        float answer = pop() * pop();
        push(answer);

        }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::sine() { //takes sine of value at the top (radians)
    if (top >= 0){ //makes sure there are enough values
        float answer = sin(pop());
        push(answer);

        }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::tangent() { //takes tangent of value at the top (radians)
    if (top >= 0){ //makes sure there are enough values
        float answer = tan(pop());
        push(answer);

        }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::cosine() { //takes cosine of value at the top (radians)
    if (top >= 0){ //makes sure there are enough values
        float answer = cos(pop());
        push(answer);

        }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::squareRoot() { //sqaureroots the value at the top
    if (top >= 0){ //makes sure there are enough values
        float answer = sqrt(pop());
        push(answer);

        }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

void Rpn::exponent() { //does x^y for the first 2 values
    if (top > 0){ //makes sure there are enough values
        float answer = pow(pop(), pop());
        push(answer);

        }
    else{
        std::cout << std::endl;
        std::cout << "More numbers are needed in stack" << std::endl;
        std::cout << std::endl;
    }
}

Rpn::~Rpn(){ //destructor
}


