/* 
 * File:   Main.c
 * Author: zhuti
 *
 * Created on September 13, 2018, 8:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "plib.h"
#include "xc.h"
#include "adc_intf.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"
#include "Button.h"
#include "Display.h"
#include "Calculator.h"

#define XM AN0
#define YP AN1

int main(int argc, char** argv) {

screen_init();

button_init();
draw_buttons();
    

    while(1)
    {
        getTSPoint();
        run();
        delay_ms(100);
       
        
        
    }
    
}

