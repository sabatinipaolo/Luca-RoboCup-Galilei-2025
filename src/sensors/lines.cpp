#include <Arduino.h>
#include "sensors/lines.h"
#include "config.h"

Lines::Lines() {
    #ifdef ROCK
    thresholds[0] = 300; //130-950
    thresholds[1] = 300; //210-960
    
    thresholds[2] = 200; //140-920
    thresholds[3] = 200; //110-840
    
    thresholds[4] = 200; //120-950
    thresholds[5] = 200; //120-900
    
    thresholds[6] = 300; //200-960
    thresholds[7] = 300; //170-960
    
    #else
    thresholds[0] = 500; //100-900
    thresholds[1] = 750; //500-950 (when ball present)

    thresholds[2] = 500; //100-850
    thresholds[3] = 500; //200-950
    
    thresholds[4] = 250; //60-480
    thresholds[5] = 750; //150-950
    
    thresholds[6] = 500; //150-900
    thresholds[7] = 500; //200-950
    
    #endif
}

void Lines::read() {
    values[0] = analogRead(Pins::LINE_N_INSIDE);
    values[1] = analogRead(Pins::LINE_N_OUTSIDE);
    values[2] = analogRead(Pins::LINE_E_INSIDE);
    values[3] = analogRead(Pins::LINE_E_OUTSIDE);
    values[4] = analogRead(Pins::LINE_S_INSIDE);
    values[5] = analogRead(Pins::LINE_S_OUTSIDE);
    values[6] = analogRead(Pins::LINE_W_INSIDE);
    values[7] = analogRead(Pins::LINE_W_OUTSIDE);
    
    status = 0;
    if(values[0] > thresholds[0]) status |= 0b10000000;
    if(values[1] > thresholds[1]) status |= 0b01000000;
    if(values[2] > thresholds[2]) status |= 0b00100000;
    if(values[3] > thresholds[3]) status |= 0b00010000;
    if(values[4] > thresholds[4]) status |= 0b00001000;
    if(values[5] > thresholds[5]) status |= 0b00000100;
    if(values[6] > thresholds[6]) status |= 0b00000010;
    if(values[7] > thresholds[7]) status |= 0b00000001;
}
