// i2c Arduino-to-Arduino chat app

#include <Wire.h>


//global vars to signify when we're sending or receiving
bool sending = false;
bool receiving = false;

//the addresses we will use on the i2c bus
byte myAddress = 4;
byte theirAddress = 3;

void setup(){
  //start i2c communication
  //define an address for ourself (3) where we can receive data
  Wire.begin(myAddress);
  //attach the receiveEvent function as an event handler for received data
  Wire.onReceive(receiveEvent);
  //begin serial communication to the attached computer
  Serial.begin(9600);
}

void loop(){
  while(Serial.available() > 0){
    //input is available from the serial port
    //read it in:
    char x = Serial.read();
    //if this is the first character...
    if(!sending){
      //print a chat heading
      Serial.print("Me: ");
      //begin the i2c transmission
      Wire.beginTransmission(theirAddress);
      //update the global var
      sending = true;
    }
    //write the received character to the i2c bus
    Serial.print(x);
    //and echo it back to the serial port
    Wire.write(x);
  }

  //this means we've reached the end of the transmission
  if(sending){
    //print a newline character to the serial port 
    Serial.println("");
    //end i2c communication
    Wire.endTransmission();
    //update the global variable
    sending = false;
  }
  
  delay(50);
}

void receiveEvent(int numBytes){
  //run this loop for as long as there are characters available
  //on the i2c bus
  while(1 < Wire.available()) {
    //check if this is the start of a new transmission
    if(!receiving){
      //update the global variable
      receiving = true;
      //print a heading to the serial port
      Serial.print("Them: ");
    }
    //continue to read a byte from the i2c bus when one is available
    char c = Wire.read();
    //print that byte straight to the computer via the serial interface
    Serial.print(c);
  }
  //read the final byte of the i2c transmission and print it 
  //using Serial.println() function - this appends a newline character
  //so each transmission appears on a new line in the serial monitor
  char x = Wire.read();
  Serial.println(x);
  //update the global variable
  receiving = false;
}
