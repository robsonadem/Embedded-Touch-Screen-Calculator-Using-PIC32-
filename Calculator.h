/* 
 * File:   Calculator.h
 * Author: Robson and Tianyu
 *
 * Created on September 13, 2018, 9:31 AM
 */

#ifndef CALCULATOR_H
#define	CALCULATOR_H
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
#include "Button.h"
#include "Display.h"

void parameter_init() ;
void UpdateNum(int value);
void UpdateDisplayNum();
void UpdateNumPress();
void printNum();
void Overflow();
void printResult();
int IsOverFlow();
int IsOverLength();
void UpdateOperationState(int N);
void run();
#endif	/* CALCULATOR_H */

