#define I2C_ROVER_ADDRESS  4

#include <Wire.h> //Needed for I2C to GPS

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println("Serial: Rover Lora Test");
  
  Wire.begin(I2C_ROVER_ADDRESS); 
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);
}

void loop() {

}

void requestEvents()
{
  Serial.println(F("Recieved request"));
}

void receiveEvents(int numBytes)
{  
  int i = 0;
  Serial.println(F("Recieved events"));
  Serial.print(numBytes);
  Serial.println(F(" bytes recieved"));
  for( int i = 0; i < numBytes; i++ ) {
    uint8_t c = Wire.read();
    Serial.write(c);
  }
  Serial.println();
}
