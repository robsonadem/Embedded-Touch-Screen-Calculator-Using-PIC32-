#include "Display.h"
#include <stdio.h>
#include <string.h>


   
        




//function that run the drawing program which display the stroke that user draws
//on the screen



//void draw() {s
//    TS_init();
//    inputNum();
//    clearBtn();
//    operation();
//    if (display_value <= 2147483647 && display_value>=0) {
//        
//        print();
//    } else {
//        Overflow();
//    }
//    
//    
//    delay_ms(100);
//}




//function that constructs the TSPoint
void getTSPoint()
{
    p.x = 0;    
    p.y = 0;
    p.z = 0;
    getPoint(&p); 
    //map the coordinate for TSPoint
    map(&p);
}


struct TSPoint returnTSPoint()
{
    getPoint(&p); 
    //map the coordinate for TSPoint
    map(&p);
    return p;
}

//Function that converts the touch screen coordinate to the pixel coordinate of 320x240
void map(struct TSPoint *p)
{       
        //data about the screen dimension
        uint16_t xmin=140;
        uint16_t xmax=900;
        uint16_t ymin=100;
        uint16_t ymax=910;
        //data about the mapped coordinate
        uint16_t newXmin=0;
        uint16_t newXmax= 240;
        uint16_t newYmin=0;
        uint16_t newYmax= 320;
        //map the current position to the new created coordinate
        int16_t newXt = ((int32_t)(p->x-xmin)*(int32_t)(newXmax-newXmin)/(int32_t)(xmax-xmin))+(int32_t)(newXmin);
        int16_t newYt = ((int32_t)(p->y-ymin)*(int32_t)(newYmax-newYmin)/(int32_t)(ymax-ymin))+(int32_t)(newYmin);
        //check the four boundaries of the screen
        if(newXt <0 )
        {
            newXt=0;
        }
        if(newYt <0)
        {
            newYt=0;
        }
        if(newXt >240 )
        {
            newXt=240;
        }
        if(newYt >320)
        {
            newYt=320;
        }
        
        uint16_t newX = newXt;
        uint16_t newY = newYt;   
        //assign the new coordinates
        p->x =newX;
        p->y =newY;
              
}

//screen initialization
void screen_init()
{
    //set the screen as black
    SYSTEMConfigPerformance(PBCLK);
    //configuration of screen
    configureADC();
    //initialize screen
    tft_init_hw();
    tft_begin();
    tft_setRotation(0); 
    tft_fillScreen(ILI9341_CYAN);  
    
}
//function that clears all screen
void clear_screen()
{
    //set screen to black
    tft_fillRect(0, 0,  240,  80,  ILI9341_CYAN);
    
}


//function that check whether the screen has been pressed, return status
int screenPressed()
{
    if(p.z>5)
    {
        return 1;
    }
    else return 0;
}


