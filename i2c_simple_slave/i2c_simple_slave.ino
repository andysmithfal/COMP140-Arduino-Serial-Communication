// i2c Arduino-to-Arduino example 
// This runs on the SLAVE Arduino

#include <Wire.h>

void setup(){
  //start i2c communication 
  //define an address for ourself (4) where we can receive data
  Wire.begin(4);
  //attach the receiveEvent function as an event handler for received data
  Wire.onReceive(receiveEvent);
  //begin serial communication to the attached computer
  Serial.begin(9600);
}

void loop(){
  delay(100);
}

void receiveEvent(int howMany){
  while(1 < Wire.available()) {
    //continue to read a byte from the i2c bus when one is available
    char c = Wire.read();
    //print that byte straight to the computer via the serial interface
    Serial.print(c);
  }
  //read the final byte of the i2c transmission and print it 
  //using Serial.println() function - this appends a newline character
  //so each transmission appears on a new line in the serial monitor
  int x = Wire.read();
  Serial.println(x);
}
