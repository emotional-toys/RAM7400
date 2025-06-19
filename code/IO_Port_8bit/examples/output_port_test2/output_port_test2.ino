#include<IO_Port_8bit.h>

IO_Port_8bit myport(2,3,4,5,6,7,8,9,0);
void setup() 
{
    
}

void loop() 
{
  int i;
  for(i=0;i<16;i++)
    {
     myport.send_8bit_data(i);
     delay(1000);
    } 
  }
