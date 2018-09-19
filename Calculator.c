/* 
 * File:   Calculator.h
 * Author: Robson and Tianyu
 *
 * This is the header file for the calculator module. 
 */

#include "Calculator.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

static char buffer[128];
static int length=0;

//variable that store the current value of the calculator 
static int32_t current_value=0;
//variable that store the previous value of the calculator 
static int32_t last_value=0;
static int32_t display_value=0;


static int32_t result=0;
static int numPress=0;
static int operationState=0;
static int last_operationState=0;
static int overflow=0;
static uint64_t tmp;
void parameter_init() {
    current_value = 0;
    display_value = 0;
    last_value = 0;
    numPress = 0;
}

void UpdateNum(int value)
{
    current_value = value;
}

void UpdateDisplayNum()
{
    display_value = display_value * 10 + current_value;
    
}
void UpdateNumPress()
{
    numPress++;
}
void UpdateOperationState(int N)
{
    operationState = N;
}

void printNum() {

    sprintf(buffer, "%ld", display_value);
    length = strlen(buffer);

    tft_setCursor(235 - 18 * length, 50);
    tft_setTextSize(3);
    tft_setTextColor(ILI9341_BLACK);
    tft_writeString(buffer);

    
}
void Overflow()
{
    clear_screen();
    sprintf(buffer, "Overflow");
        tft_setCursor(80 , 50);
        tft_setTextSize(3);
        tft_setTextColor(ILI9341_BLACK);
        tft_writeString(buffer);
}
void printResult()
{
    clear_screen();
    sprintf(buffer, "%ld", result);
    length = strlen(buffer);
    tft_setCursor(235 - 18 * length, 50);
    tft_setTextSize(3);
    tft_setTextColor(ILI9341_BLACK);
    tft_writeString(buffer);
}

int IsOverFlow()
{
    if(display_value >2147483647)
    {
        return 1;
    }
    else return 0 ;
}

int IsOverLength()
{
    if(numPress<=10)
    {
        return 1;
    }
    else return 0;
}



typedef enum {
    IDLE = 0,
    INPUT,
    OPERATION,
    RESULT,
    EQUAL,
    OVERFLOW,
} calculator_state_def;

static calculator_state_def state;


void run() {
    switch (state) {
        case IDLE:
            parameter_init();
            printNum();
            state = INPUT;
            
            break;

        case INPUT:
            if (checkNumPress()) {
                if((uint64_t)display_value>2147483647)
                {
                    Overflow();
                    state=OVERFLOW;
                }
                else
                {
                    clear_screen();
                    printNum();
                }
                    
                                 
            }
            
            if(CheckClearPress())
            {
                state = IDLE;
            }
            
            if(CheckOperationPress())
            {
                last_value=display_value;
                result = display_value;
                display_value =0;
                numPress=0;
                state = OPERATION;
            }
            break;
            
        case OPERATION:
            if (checkNumPress()) {
                    if((uint64_t)display_value>2147483647)
                {
                    Overflow();
                    state=OVERFLOW;
                }
                else
                {
                    clear_screen();
                    printNum();
                }
                    
                    if (operationState == 1) {
                        if((display_value>0 && (last_value>(INT_MAX-display_value)))||(display_value<0 && (last_value<(INT_MIN-display_value))))
                        {
                            overflow=1;
                        }
                        else
                        {
                            result = last_value + display_value;
                            overflow=0;
                        }
                        
                        
                    }
                    if (operationState == 2) {
                        if(last_value<0 && last_value - display_value > 0)
                        {
                            overflow=1;
                        }
                        else
                        {
                            result = last_value - display_value;
                            overflow=0;
                        }
                        
                    }
                    if (operationState == 3) {
                        tmp = abs(last_value) * abs(display_value);
                        if(tmp > 2147483647)
                        {
                           overflow=1;
                        }
                        else
                        {
                        result = last_value * display_value;
                        overflow=0;
                        }
                            
                        
                    }
                    if (operationState == 4) {
                        result = last_value / display_value;
                    }
                    
                    
                
            }
            
            if(CheckClearPress())
            {
                state = IDLE;
            }
            
            if(CheckOperationPress())
            {
                last_value = result;
                display_value = 0;
                numPress = 0;
                if(overflow)
                    {
                    Overflow();
                    state = OVERFLOW;
                    }
                else
                {
                printResult();
                }
            }
            
            if(checkEqual())
            {
                if(numPress==0)
                {
                    state = OPERATION;
                    break;
                }
                

                last_value=result;
                display_value =0;
                numPress=0;
                if(overflow)
                    {
                    Overflow();
                    state = OVERFLOW;
                    }
                else
                {
                printResult();
                }
                state = EQUAL;
            }
            
            break;
            
            
        case OVERFLOW:
            if(CheckClearPress())
            {
              overflow=0;
              state = IDLE;
            }
            break;
            
        case EQUAL:
            if (checkNumPress()) {
                    if((uint64_t)display_value>2147483647)
                {
                    Overflow();
                    state=OVERFLOW;
                }
                else
                {
                    clear_screen();
                    printNum();
                    state = INPUT;
                }
                    
                
            }

            if (CheckClearPress()) {
                state = IDLE;
            }

            if (CheckOperationPress()) {

                state = OPERATION;
            }
            break;
    }
    
    
}






















































