#include<IO_Port_8bit.h>

IO_Port_8bit myport(2,3,4,5,6,7,8,9,1);
void setup() 
{
    Serial.begin(9600);
    Serial.println("8-bit input port test");
}

void loop() 
{
  int input_byt;
  input_byt = myport.get_8bit_data();
  Serial.print("received input = ");
  Serial.println(input_byt);
  delay(1000);
  }
