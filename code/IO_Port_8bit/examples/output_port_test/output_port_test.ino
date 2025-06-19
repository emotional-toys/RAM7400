#include<IO_Port_8bit.h>

IO_Port_8bit myport(2,3,4,5,6,7,8,9,0);
void setup() 
{
    
}

void loop() 
{
  myport.send_8bit_data(85);
  delay(500);
  myport.send_8bit_data(170);
  delay(500);
}
