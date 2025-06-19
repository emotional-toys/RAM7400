
/* Port library for Arduino
created by Ashutosh M Bhatt (+91-9998476150) - Gujarat (INDIA) 
ver 1.0 - on 25/11/2018
using this library one can send direct 8 bit data to any arduino board pins
configured combined as a 8-bit port
also one can get 8-bit input from these configured pins
just one has to select any 8 arduino pins to be combined as 8-bit port 
and it has to configure its data direction as input or output
data direction is 'O' for port as output and 'I' for port as input
*/
#include "IO_Port_8bit.h"
#include "Arduino.h"
/*
this is constructor. it will create object(s) of this class and thus it will create one or many 8-bit port(s) by
combining distinct arduino pins. one has to specify 8 different arduino pins to be combined as port along with 
data direction as input or output - means port works as either input or output. the last argument dir in this constructor
defines port works as input or output. if dir='O' means port work as output and if dir='I', port works as input
the same port can not work as input and output both simulteneously or even alternatively. also it indicates error if data 
direction is not selected  
*/
IO_Port_8bit::IO_Port_8bit(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6,int pin7,int pin8,char dir)
  {
      pin_1 = pin1;
      pin_2 = pin2;
      pin_3 = pin3;
      pin_4 = pin4;
      pin_5 = pin5;
      pin_6 = pin6;
      pin_7 = pin7;
      pin_8 = pin8;
      if(dir=='O')
        {
          pinMode(pin1,OUTPUT);  
          pinMode(pin2,OUTPUT); 
          pinMode(pin3,OUTPUT); 
          pinMode(pin4,OUTPUT); 
          pinMode(pin5,OUTPUT); 
          pinMode(pin6,OUTPUT); 
          pinMode(pin7,OUTPUT); 
          pinMode(pin8,OUTPUT);  
        }      
      else if(dir=='I')
        {
           pinMode(pin1,INPUT);   
           pinMode(pin2,INPUT);  
           pinMode(pin3,INPUT);  
           pinMode(pin4,INPUT);  
           pinMode(pin5,INPUT);  
           pinMode(pin6,INPUT);  
           pinMode(pin7,INPUT);  
           pinMode(pin8,INPUT);     
        } 
      else
        Serial.println("Error! The data direction (Input/Output) for port is not selected");  
   }
/*
this is another constructor. it will create object(s) of this class and thus it will create one or many 8-bit port(s) by
combining distinct arduino pins. one has to specify 8 different arduino pins to be combined as port. but it does not 
specify the data direction as input or output. after creating port object using this constructor one has to set the port
direction using set_IO_direction function. so this constructor allows programmer to alter port data direction in run time
using this constructor, the same port can work as input or output alternatively (but not simulteneously)
*/
IO_Port_8bit::IO_Port_8bit(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6,int pin7,int pin8)
  {
      pin_1 = pin1;
      pin_2 = pin2;
      pin_3 = pin3;
      pin_4 = pin4;
      pin_5 = pin5;
      pin_6 = pin6;
      pin_7 = pin7;
      pin_8 = pin8;      
  }   
/* this function specifies the input/output direction of port. it has one character argument that can be 
'I' for port as input or 'O' for port as output. if data direction is not selected, it displays error on
serial monitor of arduino */
void IO_Port_8bit::set_IO_direction(char dir)
  {
     if(dir=='O')
        {
          pinMode(pin_1,OUTPUT);  
          pinMode(pin_2,OUTPUT); 
          pinMode(pin_3,OUTPUT); 
          pinMode(pin_4,OUTPUT); 
          pinMode(pin_5,OUTPUT); 
          pinMode(pin_6,OUTPUT); 
          pinMode(pin_7,OUTPUT); 
          pinMode(pin_8,OUTPUT);  
        }      
      else if(dir=='I')
        {
           pinMode(pin_1,INPUT);   
           pinMode(pin_2,INPUT);  
           pinMode(pin_3,INPUT);  
           pinMode(pin_4,INPUT);  
           pinMode(pin_5,INPUT);  
           pinMode(pin_6,INPUT);  
           pinMode(pin_7,INPUT);  
           pinMode(pin_8,INPUT);     
        } 
      else
        Serial.println("Error! The data direction (Input/Output) for port is not selected");  
  }                          
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
// this function sends 8 bit data to specified pins. just give int data (must be < 255) as an argument that is directly given to 
//8 different pins. if data is >255 it displays error on serial monitor of arduino
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void IO_Port_8bit::send_8bit_data(int byt)
   {
      int d=0;
      int binary[8] = {0,0,0,0,0,0,0,0};
      Serial.begin(9600);
      if (byt>255) Serial.println("Error! You are trying to send data having value greater than 8-bit (>255)");
      else
       {
          while(byt>0)
          {
            binary[d] = byt%2;
            byt = byt/2;
            d++; 
          }
          if(binary[0]==1) digitalWrite(pin_1,HIGH);
          else digitalWrite(pin_1,LOW);
          if(binary[1]==1) digitalWrite(pin_2,HIGH);
          else digitalWrite(pin_2,LOW);
          if(binary[2]==1) digitalWrite(pin_3,HIGH);
          else digitalWrite(pin_3,LOW);
          if(binary[3]==1) digitalWrite(pin_4,HIGH);
          else digitalWrite(pin_4,LOW);
          if(binary[4]==1) digitalWrite(pin_5,HIGH);
          else digitalWrite(pin_5,LOW);
          if(binary[5]==1) digitalWrite(pin_6,HIGH);
          else digitalWrite(pin_6,LOW);
          if(binary[6]==1) digitalWrite(pin_7,HIGH);
          else digitalWrite(pin_7,LOW);
          if(binary[7]==1) digitalWrite(pin_8,HIGH);
          else digitalWrite(pin_8,LOW);
       }  
  } 
  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
// this function gets 8 bit data from specified pins. it returns 8-bit int data by reading status of 8 different pins  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
int IO_Port_8bit::get_8bit_data(void)
  {
      int byt;
      int bin[8];
      bin[0] = digitalRead(pin_1);
      bin[1] = digitalRead(pin_2);
      bin[2] = digitalRead(pin_3);
      bin[3] = digitalRead(pin_4);
      bin[4] = digitalRead(pin_5);
      bin[5] = digitalRead(pin_6);
      bin[6] = digitalRead(pin_7);
      bin[7] = digitalRead(pin_8);
      byt = 128*bin[7]+64*bin[6]+32*bin[5]+16*bin[4]+8*bin[3]+4*bin[2]+2*bin[1]+bin[0]; 
      return byt;
  }              
