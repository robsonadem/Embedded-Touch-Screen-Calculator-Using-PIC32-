/* 
 * File:   Display.h
 * Author: Robson & Tianyu
 * This module handles all the display functionalities for the calculator module. 
 */

#ifndef DISPLAY_H
#define	DISPLAY_H


#include <p32xxxx.h>
#include <inttypes.h>

#include "plib.h"
#include "xc.h"
#include "adc_intf.h"
#include "Button.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"
#include "Calculator.h"
//the TSPoint structure variable that indicate the current pixel 
struct TSPoint p;





//function that initializes the TSPoint and map its coordinates 
void getTSPoint();
//function that starts the drawing program 
void draw();

//function that initializes the screen
void screen_init();
//function that map the coordinate of the TSPoint
void map(struct TSPoint *p);

void clear_screen();
//function that check whether the screen has been pressed
int screenPressed();

void printNum();
void Overflow();

#endif	/* DISPLAY_H */

