// Updated for PIC32 by Matthew Watkins

// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#include "TouchScreen.h"

#include "plib.h"
#include "xc.h"
#include "adc_intf.h"

// increase or decrease the touchscreen oversampling. This is a little different than you make think:
// 1 is no oversampling, whatever data we get is immediately returned
// 2 is double-sampling and we only return valid data if both points are the same
// 3+ uses insert sort to get the median value.
// Adafruit: We found 2 is precise yet not too slow so we suggest sticking with it!
// MWatkins: With parallel communication found 3 samples more reliable

#define NUMSAMPLES 3


#if (NUMSAMPLES > 2)
static void insert_sort(int array[], uint8_t size) {
  uint8_t j;
  int s; //was save
  
  int i;
  for (i = 1; i < size; i++) {
    s = array[i];
    for (j = i; j >= 1 && s < array[j - 1]; j--)
      array[j] = array[j - 1];
    array[j] = s; 
  }
}
#endif

void setTSPoint(struct TSPoint * p, int16_t x0, int16_t y0, int16_t z0){
    p->x = x0;
    p->y = y0;
    p->z = z0;
}

void getPoint(struct TSPoint * p) {
  int x=0, y=0, z=0;
  int samples[NUMSAMPLES];
  uint8_t i, valid;
  
  valid = 1;

  mPORTASetPinsDigitalIn(YMbit);
  mPORTASetPinsAnalogIn(YPbit);
  
  mPORTAClearBits(YPbit | YMbit);

  mPORTASetPinsDigitalOut(XPbit | XMbit);
  mPORTASetBits(XPbit);
  mPORTAClearBits(XMbit);
   
   for (i=0; i<NUMSAMPLES; i++) {
       samples[i] = readADC(YPAN);
     //samples[i] = analogRead(_yp);
   }
#if NUMSAMPLES > 2
   insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
   if (samples[0] != samples[1]) { valid = 0; }
#endif
   x = (1023-samples[NUMSAMPLES/2]);

   mPORTASetPinsDigitalIn(XPbit);
   mPORTASetPinsAnalogIn(XMbit);
   mPORTAClearBits(XPbit);
   
   mPORTASetPinsDigitalOut(YPbit | YMbit);
   mPORTASetBits(YPbit);
   mPORTAClearBits(YMbit);
  
   for (i=0; i<NUMSAMPLES; i++) {
       samples[i] = readADC(XMAN);
     //samples[i] = analogRead(_xm);
   }

#if NUMSAMPLES > 2
   insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
   if (samples[0] != samples[1]) { valid = 0; }
#endif

   y = (1023-samples[NUMSAMPLES/2]);

   // Set X+ to ground
   mPORTASetPinsDigitalOut(XPbit);
   mPORTAClearBits(XPbit);

  
   // Set Y- to VCC
   mPORTASetBits(YMbit);
  
   // Hi-Z X- and Y+
   mPORTAClearBits(YPbit);
   mPORTASetPinsAnalogIn(YPbit);
  
   int z1 = readADC(XMAN);
   int z2 = readADC(YPAN);

   if (RXPLATE != 0) {
     // now read the x 
     float rtouch;
     rtouch = z2;
     rtouch /= z1;
     rtouch -= 1;
     rtouch *= x;
     rtouch *= RXPLATE;
     rtouch /= 1024;
     
     z = rtouch;
   } else {
     z = (1023-(z2-z1));
   }

   if (! valid) {
     z = 0;
   }

   //printf("Internal point %d, %d, %d\n", x, y, z);
   
   setTSPoint(p, x, y, z);
}

// Individual X and Y read not implemented at moment for PIC 32
// Could be created by extracting relevant pieces of getPoint
/*
int readTouchX(void) {
   pinMode(_yp, INPUT);
   pinMode(_ym, INPUT);
   digitalWrite(_yp, LOW);
   digitalWrite(_ym, LOW);
   
   pinMode(_xp, OUTPUT);
   digitalWrite(_xp, HIGH);
   pinMode(_xm, OUTPUT);
   digitalWrite(_xm, LOW);
   
   return (1023-analogRead(_yp));
}


int readTouchY(void) {
   pinMode(_xp, INPUT);
   pinMode(_xm, INPUT);
   digitalWrite(_xp, LOW);
   digitalWrite(_xm, LOW);
   
   pinMode(_yp, OUTPUT);
   digitalWrite(_yp, HIGH);
   pinMode(_ym, OUTPUT);
   digitalWrite(_ym, LOW);
   
   return (1023-analogRead(_xm));
}


uint16_t pressure(void) {
  // Set X+ to ground
  pinMode(_xp, OUTPUT);
  digitalWrite(_xp, LOW);
  
  // Set Y- to VCC
  pinMode(_ym, OUTPUT);
  digitalWrite(_ym, HIGH); 
  
  // Hi-Z X- and Y+
  digitalWrite(_xm, LOW);
  pinMode(_xm, INPUT);
  digitalWrite(_yp, LOW);
  pinMode(_yp, INPUT);
  
  int z1 = analogRead(_xm); 
  int z2 = analogRead(_yp);

  if (_rxplate != 0) {
    // now read the x 
    float rtouch;
    rtouch = z2;
    rtouch /= z1;
    rtouch -= 1;
    rtouch *= readTouchX();
    rtouch *= _rxplate;
    rtouch /= 1024;
    
    return rtouch;
  } else {
    return (1023-(z2-z1));
  }
}*/
