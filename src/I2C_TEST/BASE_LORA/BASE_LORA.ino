#define I2C_LORA_ADDRESS  4

#include <Wire.h> //Needed for I2C to GPS

void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB)
    ; //Wait for user to open terminal
  SerialUSB.println("Serial: Lora Radio Test");
  
  Wire.begin(I2C_LORA_ADDRESS); // transmit to device I2C_LORA_ADDRESS
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
  SerialUSB.println(F("Recieved events"));
  SerialUSB.print(numBytes);
  SerialUSB.println(F(" bytes recieved"));
  for( int i = 0; i < numBytes; i++ ) {
    uint8_t c = Wire.read();
    SerialUSB.write(c);
  }
  SerialUSB.println();
}
