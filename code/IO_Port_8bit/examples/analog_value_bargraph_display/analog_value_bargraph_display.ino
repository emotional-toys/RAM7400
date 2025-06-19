#include<IO_Port_8bit.h>

IO_Port_8bit myport(2,3,4,5,6,7,8,9,0);
void setup() 
{
  myport.send_8bit_data(255);
  delay(500);
  myport.send_8bit_data(0);
}

void loop() 
{
   int level;
   level = analogRead(A0);
   level = map(level,0,1023,0,80);
    if(level=>80) myport.send_8bit_data(255);
    else if((level<80) && (level>70)) myport.send_8bit_data(127); 
    else if((level<=70) && (level>60)) myport.send_8bit_data(63); 
    else if((level<=60) && (level>50)) myport.send_8bit_data(31);
    else if((level<=50) && (level>40)) myport.send_8bit_data(15);
    else if((level<=40) && (level>30)) myport.send_8bit_data(7); 
    else if((level<=30) && (level>20)) myport.send_8bit_data(3);
    else if(level<=20) myport.send_8bit_data(1); 
}
