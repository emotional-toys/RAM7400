/* Port library for Arduino
created by Ashutosh M Bhatt (+91-9998476150) - Gujarat (INDIA) 
ver 1.0 - on 25/11/2018
using this library one can send direct 8 bit data to any arduino board pins
configured as a combined 8-bit port
also one can get 8-bit input from these configured pins
just one has to select any 8 arduino pins to be combined as 8-bit port 
and it has to configure its data direction as input or output
data direction is 'O' for port as output and 'I' for port as input
*/
#ifndef IO_Port_8bit_h
#define IO_Port_8bit_h

#include "Arduino.h"

class IO_Port_8bit
  { 
    private:
            int pin_1,pin_2,pin_3,pin_4,pin_5,pin_6,pin_7,pin_8;            
    public:
    IO_Port_8bit(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6,int pin7,int pin8,char dir);
    IO_Port_8bit(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6,int pin7,int pin8);
    void set_IO_direction(char dir);
    void send_8bit_data(int byt);
    int get_8bit_data(void);
 };
  
#endif