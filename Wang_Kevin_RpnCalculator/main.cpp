/*****************************************************************************
 *	Name:   Kevin Wang
 *	File:   main.cpp
 *	Course: ICS4U
 *	Date:   April 4, 2018
 *
 *	Purpose: To run a reverse polish notation calculator using allegro
 *           This version uses a array which push
 *           and pops numbers to and from the stack
 *
 *
 *	Usage:  Uses both allegro display and console to inform the user
 *          Must press push after every fully inputed number
 *          Other buttons do not need to press push
 *          Press AC/OFF button once to clear and another to close
 *
 *	Revision History: N/A
 *
 *	Known Issues: N/A
 *
 *****************************************************************************/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <apstring.h>
#include <apstring.cpp>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "rpn.h"

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0 ,0)
#define GREY al_map_rgb(220, 220, 220)
#define ORANGE al_map_rgb(255, 160, 0)

using namespace std;

ALLEGRO_DISPLAY *display = nullptr;         //declare display
ALLEGRO_EVENT_QUEUE *event_queue = NULL;	//to store events such as clicks, etc
ALLEGRO_FONT *font = NULL;                  //declare fonts
ALLEGRO_FONT *smallerFont = NULL;
const int SCREEN_HEIGHT = 390;
const int SCREEN_WIDTH = 240;

//creates the interface display
void createDisplay();

//initializes all of allegros events
void initializeEvents();

//checks where the usre clicked and returns a specific character
char checkClick(int x, int y);

//prints out the answer to the calculator screen
void printAnswer(Rpn calc);

//prints out the user input onto the calculator screen
void printInput(apstring expression);

int main() {
    //initializes allegro
    if(!al_init()) {
      std::cerr << "failed to initialize allegro!" << std::endl;
      return -1;
    }

    Rpn Calc; //main Rpn variable
    bool exit = false; //variable for the main loop
    int pos_x;  //mouse position x
    int pos_y;  //mouse position y
    char ch1[1]; //holds the character returned from the checkClick funtion
    apstring expression(""); //user input
    int dotCounter = 0; //counter to make sure if user presses too many '.'
    int Ac_OffCounter = 0; //if user wants to turn off calculator, they must click AC/OFF button twice
                           //clicking once will clear stack
                           //also, user must push a number in before clearing stack or else calculator will turn off

    initializeEvents();
    createDisplay();

    while (!exit){

        ALLEGRO_EVENT ev; //creates an allegro event
		al_wait_for_event(event_queue, &ev); //waits for an event to happen

		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { //if a mouse button was released on the calculator

			pos_x = ev.mouse.x; //get x position
			pos_y = ev.mouse.y; //get y position

            if (ev.mouse.button & 1){ //if left mouse button was clicked

                ch1[0] = checkClick(pos_x, pos_y); //return the character to decide what to do

                if (ch1[0] != '+' && ch1[0] != '-' &&
                    ch1[0] != '/' && ch1[0] != '*' &&
                    ch1[0] != 'P' && ch1[0] != 'D' &&
                    ch1[0] != 'S' && ch1[0] != 'T' &&
                    ch1[0] != 'C' && ch1[0] != 'O' &&
                    ch1[0] != '.' && ch1[0] != '(' &&
                    ch1[0] != 'R' && ch1[0] != '^'){ //input of a number

                        expression += ch1[0];
                        printInput(expression);
                }
                else if (ch1[0] == '.'){ //add a point to the number
                    if (dotCounter == 0){ //to check if the user already pressed '.' for the number

                        expression += ".";

                        printInput(expression);

                        dotCounter++;
                    }
                }
                //applying negative sign only works with the number you are currently inputting
                else if (ch1[0] == '('){
                    if (expression != ""){ //if there are already characters

                        if(expression[0] == '-'){ //make number positive if already negative
                            expression = expression.substr(1, expression.length());
                            printInput(expression);
                        }
                        else { //add negative to front
                            expression = "-" + expression;
                            printInput(expression);
                        }
                    }
                    else { //put negative in expression
                        expression = "-";
                        printInput(expression);
                    }
                }
                else if (ch1[0] == 'D'){ //delete first number in list
                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to delete
                        al_draw_filled_rectangle(0,0,SCREEN_WIDTH,89, BLACK); //clears the calculator screen
                        al_flip_display();

                        Calc.Delete();

                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    else
                        cout << "No number to delete" << endl;
                }
                else if (ch1[0] == 'O'){ //clear whole list for first click and turn off calc for second
                    if (Ac_OffCounter == 0){ //erase all contents
                        al_draw_filled_rectangle(0,0,SCREEN_WIDTH,89, BLACK);
                        al_flip_display();

                        Calc.eraseAll();

                        Ac_OffCounter++;
                    }
                    else{ //turn off calc
                        al_destroy_display(display);
                        al_destroy_event_queue(event_queue);
                        exit = true;
                    }

                }
                else if (ch1[0] == 'P'){ //push in the number inputed

                     if (expression != ""){

                        Calc.push(atof(expression.c_str()));
                        //refresh all the variables
                        dotCounter = 0;
                        Ac_OffCounter = 0;
                        expression = "";

                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                     }
                }
                else if (ch1[0] == '+'){ //adds
                    Calc.add();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == '-'){ //subtracts
                    Calc.subtract();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == '/'){ //divides
                    Calc.divide();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == '*'){ //multiplies
                    Calc.multiply();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == 'S'){ //sine
                    Calc.sine();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == 'T'){ //tangent
                    Calc.tangent();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == 'C'){ //cosine
                    Calc.cosine();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == 'R'){ //sqaure root
                    Calc.squareRoot();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
                else if (ch1[0] == '^'){ //exponents
                    Calc.exponent();

                    if (Calc.returnTopIndex() != -1){ //makes sure there is a number to print
                        printAnswer(Calc);
                        cout << "Current Stack: ";
                        Calc.printStack();
                        cout << endl << endl;
                    }
                    expression = "";
                }
            }
            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                exit = false;
            }
        }
    }
    return 0;
}

void createDisplay(){ //prints out all the initial calculator display
    //AC and OFF button
    al_draw_filled_rectangle(120,90,180,140, al_map_rgb(128,128,255));
    al_draw_filled_rectangle(180,90,239,140, al_map_rgb(255, 0, 0));
    //number buttons, '.', and '(-)'
    al_draw_filled_rectangle(2,190,60,240, ORANGE);
    al_draw_filled_rectangle(60,190,120,240, ORANGE);
    al_draw_filled_rectangle(120,190,180,240, ORANGE);
    al_draw_filled_rectangle(2,240,60,290, ORANGE);
    al_draw_filled_rectangle(60,240,120,290, ORANGE);
    al_draw_filled_rectangle(120,240,180,290, ORANGE);
    al_draw_filled_rectangle(2,290,60,340, ORANGE);
    al_draw_filled_rectangle(60,290,120,340, ORANGE);
    al_draw_filled_rectangle(120,290,180,340, ORANGE);
    al_draw_filled_rectangle(2,340,60,389, ORANGE);
    al_draw_filled_rectangle(60,340,120,389, ORANGE);
    al_draw_filled_rectangle(120,340,180,389, ORANGE);
    //other buttons
    al_draw_filled_rectangle(2,90,60,140, GREY);
    al_draw_filled_rectangle(60,90,120,140, GREY);
    al_draw_filled_rectangle(2,140,60,190, GREY);
    al_draw_filled_rectangle(60,140,120,190, GREY);
    al_draw_filled_rectangle(120,140,180,190, GREY);
    al_draw_filled_rectangle(180,140,239,190, GREY);
    al_draw_filled_rectangle(180,190,239,240, GREY);
    al_draw_filled_rectangle(180,240,239,290, GREY);
    al_draw_filled_rectangle(180,290,239,340, GREY);
    al_draw_filled_rectangle(180,340,239,389, GREY);

    al_draw_filled_rectangle(0,0,SCREEN_WIDTH,89, BLACK);

    al_draw_textf(font, BLACK, 30, 100, ALLEGRO_ALIGN_CENTRE, "√");
    al_draw_textf(font, BLACK, 90, 100, ALLEGRO_ALIGN_CENTRE, "^");
    al_draw_textf(font, WHITE, 150, 100, ALLEGRO_ALIGN_CENTRE, "del");
    al_draw_textf(smallerFont, WHITE, 208, 105, ALLEGRO_ALIGN_CENTRE, "AC/OFF");

    al_draw_rectangle(2,90,60,140, BLACK, 1.0);
    al_draw_rectangle(60,90,120,140, BLACK, 1.0);
    al_draw_rectangle(120,90,180,140, BLACK, 1.0);
    al_draw_rectangle(180,90,239,140, BLACK, 1.0);

    al_draw_textf(font, BLACK, 30, 150, ALLEGRO_ALIGN_CENTRE, "sin");
    al_draw_textf(font, BLACK, 90, 150, ALLEGRO_ALIGN_CENTRE, "tan");
    al_draw_textf(font, BLACK, 150, 150, ALLEGRO_ALIGN_CENTRE, "cos");
    al_draw_textf(font, BLACK, 210, 150, ALLEGRO_ALIGN_CENTRE, "+");

    al_draw_rectangle(2,140,60,190, BLACK, 1.0);
    al_draw_rectangle(60,140,120,190, BLACK, 1.0);
    al_draw_rectangle(120,140,180,190, BLACK, 1.0);
    al_draw_rectangle(180,140,239,190, BLACK, 1.0);

    al_draw_textf(font, WHITE, 30, 200, ALLEGRO_ALIGN_CENTRE, "7");
    al_draw_textf(font, WHITE, 90, 200, ALLEGRO_ALIGN_CENTRE, "8");
    al_draw_textf(font, WHITE, 150, 200, ALLEGRO_ALIGN_CENTRE, "9");
    al_draw_textf(font, BLACK, 210, 200, ALLEGRO_ALIGN_CENTRE, "-");

    al_draw_rectangle(2,190,60,240, BLACK, 1.0);
    al_draw_rectangle(60,190,120,240, BLACK, 1.0);
    al_draw_rectangle(120,190,180,240, BLACK, 1.0);
    al_draw_rectangle(180,190,239,240, BLACK, 1.0);

    al_draw_textf(font, WHITE, 30, 250, ALLEGRO_ALIGN_CENTRE, "4");
    al_draw_textf(font, WHITE, 90, 250, ALLEGRO_ALIGN_CENTRE, "5");
    al_draw_textf(font, WHITE, 150, 250, ALLEGRO_ALIGN_CENTRE, "6");
    al_draw_textf(font, BLACK, 210, 250, ALLEGRO_ALIGN_CENTRE, "x");

    al_draw_rectangle(2,240,60,290, BLACK, 1.0);
    al_draw_rectangle(60,240,120,290, BLACK, 1.0);
    al_draw_rectangle(120,240,180,290, BLACK, 1.0);
    al_draw_rectangle(180,240,239,290, BLACK, 1.0);

    al_draw_textf(font, WHITE, 30, 300, ALLEGRO_ALIGN_CENTRE, "1");
    al_draw_textf(font, WHITE, 90, 300, ALLEGRO_ALIGN_CENTRE, "2");
    al_draw_textf(font, WHITE, 150, 300, ALLEGRO_ALIGN_CENTRE, "3");
    al_draw_textf(font, BLACK, 210, 300, ALLEGRO_ALIGN_CENTRE, "/");

    al_draw_rectangle(2,290,60,340, BLACK, 1.0);
    al_draw_rectangle(60,290,120,340, BLACK, 1.0);
    al_draw_rectangle(120,290,180,340, BLACK, 1.0);
    al_draw_rectangle(180,290,239,340, BLACK, 1.0);

    al_draw_textf(font, WHITE, 30, 350, ALLEGRO_ALIGN_CENTRE, "0");
    al_draw_textf(font, WHITE, 90, 350, ALLEGRO_ALIGN_CENTRE, ".");
    al_draw_textf(font, WHITE, 150, 350, ALLEGRO_ALIGN_CENTRE, "( - )");
    al_draw_textf(font, BLACK, 210, 350, ALLEGRO_ALIGN_CENTRE, "push");

    al_draw_rectangle(2,340,60,389, BLACK, 1.0);
    al_draw_rectangle(60,340,120,389, BLACK, 1.0);
    al_draw_rectangle(120,340,180,389, BLACK, 1.0);
    al_draw_rectangle(180,340,239,389, BLACK, 1.0);

    al_flip_display();

}

void initializeEvents(){

    //initializes display
    display = al_create_display (SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display){
        cerr << "failed to create display! " << endl;
    }

    //initializes event queue
    event_queue = al_create_event_queue ();
    if (!event_queue){
        cerr << "failed to create event_queue!" << endl;
        al_destroy_display (display);
    }

    //installs and initializes mouse
    if(!al_install_mouse()) {
		cerr << "failed to initialize mouse!" << endl;
	}

    //initializes primitives addon
    al_init_primitives_addon();

    //initializes font addon
    al_init_font_addon();

    // initialize the ttf (True Type Font) addon
    al_init_ttf_addon();

    //loads font files
    font = al_load_ttf_font("trb.ttf", 25, 0);
    if (!font){
        cerr << "failed to create font!";
    }

    smallerFont = al_load_ttf_font("trb.ttf", 15, 0);
    if (!font){
        cerr << "failed to create font!";
    }

    //registers even sources for display and mouse
    al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

}

char checkClick(int x, int y){

    if (x >= 2 && x <= 60 && y >= 90 && y <= 140)
        return 'R';
    else if (x >= 60 && x <= 120 && y >= 90 && y <= 140)
        return '^';
    else if (x >= 120 && x <= 180 && y >= 90 && y <= 140)
        return 'D';
    else if (x >= 180 && x <= 239 && y >= 90 && y <= 140)
        return 'O';
    else if (x >= 2 && x <= 60 && y >= 140 && y <= 190)
        return 'S';
    else if (x >= 60 && x <= 120 && y >= 140 && y <= 190)
        return 'T';
    else if (x >= 120 && x <= 180 && y >= 140 && y <= 190)
        return 'C';
    else if (x >= 180 && x <= 239 && y >= 140 && y <= 190)
        return '+';
    else if (x >= 2 && x <= 60 && y >= 190 && y <= 240)
        return '7';
    else if (x >= 60 && x <= 120 && y >= 190 && y <= 240)
        return '8';
    else if (x >= 120 && x <= 180 && y >= 190 && y <= 240)
        return '9';
    else if (x >= 180 && x <= 239 && y >= 190 && y <= 240)
        return '-';
    else if (x >= 2 && x <= 60 && y >= 240 && y <= 290)
        return '4';
    else if (x >= 60 && x <= 120 && y >= 240 && y <= 290)
        return '5';
    else if (x >= 120 && x <= 180 && y >= 240 && y <= 290)
        return '6';
    else if (x >= 180 && x <= 239 && y >= 240 && y <= 290)
        return '*';
    else if (x >= 2 && x <= 60 && y >= 290 && y <= 340)
        return '1';
    else if (x >= 60 && x <= 120 && y >= 290 && y <= 340)
        return '2';
    else if (x >= 120 && x <= 180 && y >= 290 && y <= 340)
        return '3';
    else if (x >= 180 && x <= 239 && y >= 290 && y <= 340)
        return '/';
     else if (x >= 2 && x <= 60 && y >= 340 && y <= 389)
        return '0';
    else if (x >= 60 && x <= 120 && y >= 340 && y <= 389)
        return '.';
    else if (x >= 120 && x <= 180 && y >= 340 && y <= 389)
        return '('; // for negative sign
    else if (x >= 180 && x <= 239 && y >= 340 && y <= 389)
        return 'P';
}

void printAnswer(Rpn calc){ //prints answer onto calculator screen

    string answer = to_string(calc.peek());
    al_draw_filled_rectangle(0,0,SCREEN_WIDTH,89, BLACK);
    al_draw_textf(font, WHITE, 10, 20, ALLEGRO_ALIGN_LEFT, answer.c_str());
    al_flip_display();

}

void printInput(apstring expression){ //prints the user input onto the calculator screen

    al_draw_filled_rectangle(0,0,SCREEN_WIDTH,89, BLACK);
    al_draw_textf(font, WHITE, 10, 20, ALLEGRO_ALIGN_LEFT, expression.c_str());
    al_flip_display();
}


