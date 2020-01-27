// i2c Arduino-to-Arduino example 
// This runs on the MASTER Arduino

#include <Wire.h>

//one byte (8 bits) acts as a counter 
byte x = 0;

void setup(){
  //start i2c communication
  //we don't need to define an address as we won't 
  //be receiving data 
  Wire.begin();
}

void loop(){
  //select a slave to transmit to (address number 4)
  Wire.beginTransmission(4);
  //write data to the i2c bus
  Wire.write("x is ");
  Wire.write(x);
  //end the transmission
  Wire.endTransmission();
  //increment the counter var
  x++; 
  //delay so we don't flood the bus with data
  delay(50);
}
