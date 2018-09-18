/* 
 * File:   Button.h
 * Author: zhuti
 *
 * Created on September 13, 2018, 8:21 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H
#include <p32xxxx.h>
#include <inttypes.h>
#include "Display.h"


////create button structure variable contains the x,y coordinates, width,height and
////color of the button
//struct button
//{
//    uint16_t x, y, w, h;
//    uint16_t color;
//    unsigned char name;
//};
////create 6 color buttons and one clear button
//struct button btn0,btn1, btn2, btn3,btn4,btn5,btn6,btn7,btn8,btn9,btnC,btnEqual,btnAdd,btnSub,btnMul,btnDiv;

//function that initializes all the buttons on the screen 
void button_init();
//functions that draw the given button outline with its color

//function that draws the outline of the button on specified position
void draw_buttons();
//function that check whether a specific button is pressed or not

int checkNumPress();

int CheckOperationPress();
int checkEqual();

int CheckClearPress();
#endif	/* BUTTON_H */

