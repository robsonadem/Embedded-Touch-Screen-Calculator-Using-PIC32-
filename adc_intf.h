/* 
 * File:   adc_intf.h
 * Author: Matthew Watkins
 *
 * Created on September 2, 2015, 9:56 AM
 */

#ifndef ADC_INTF_H
#define	ADC_INTF_H

#include "plib.h"
#include "xc.h"

#ifdef	__cplusplus
extern "C" {
#endif

//ADC
// Define setup parameters for OpenADC10 function
// Turn module on | Output in integer format | Trigger mode auto | Enable autosample
#define config1     ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF 
// ADC ref external | Disable offset test | Disable scan mode | Perform 2 samples | Use dual buffers | Use alternate mode
#define config2     ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 
// Use ADC internal clock | Set sample time
//Use PB clock (default)), 15*Tad, conversion 4 
#define config3      ADC_CONV_CLK_PB | ADC_SAMPLE_TIME_15 | ADC_CONV_CLK_Tcy
// Do not assign channels to scan
#define configscan  0
#define configport 0

    
void configureADC();

int readADC(int an);

int analogRead(char analogPIN);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_INTF_H */

