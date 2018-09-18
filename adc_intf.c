#include "adc_intf.h"
#include "plib.h"
#include "xc.h"

int analogRead(char analogPIN){
    //AD1CHS = analogPIN << 16;       // AD1CHS<16:19> controls which analog pin goes to the ADC
    SetChanADC10(analogPIN << 16);
    
    //AD1CON1bits.SAMP = 1;           // Begin sampling
    AcquireADC10();
    while( AD1CON1bits.SAMP );      // wait until acquisition is done
    while( ! AD1CON1bits.DONE );    // wait until conversion done
 
    //return ADC1BUF0;                // result stored in ADC1BUF0
    return ReadADC10(0);
}

/*  Configure achieves the same as the following register manipulation
    AD1CON1CLR = 0x8000;    // disable ADC before configuration
 
    AD1CON1 = 0x00E0;       // internal counter ends sampling and starts conversion (auto-convert), manual sample
    AD1CON2 = 0;            // AD1CON2<15:13> set voltage reference to pins AVSS/AVDD
    AD1CON3 = 0x0f01;       // TAD = 4*TPB, acquisition time = 15*TAD 
 */
void configureADC(){
    //ADC
    CloseADC10();

    // Could configure desired channel here
    // Configure to sample AN0 & AN1
    // Use ground as neg ref for A | use AN0 for input A | use ground as neg ref for A | use AN2 for input B
    //SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN0 |  ADC_CH0_NEG_SAMPLEB_NVREF | ADC_CH0_POS_SAMPLEB_AN1);
   
    OpenADC10(config1, config2, config3, configport, configscan);
    EnableADC10(); // Enable the ADC
}


int readADC(int an) {
    return analogRead(an);
}