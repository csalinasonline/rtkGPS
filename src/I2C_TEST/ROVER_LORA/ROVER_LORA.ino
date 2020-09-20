#define I2C_LORA_ADDRESS  4

#include <Wire.h> //Needed for I2C to GPS

void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB)
    ; //Wait for user to open terminal
  SerialUSB.println("Serial: Lora Test");

  Wire.setClock(400000); //Increase I2C clock speed to 400kHz
  Wire.begin(I2C_LORA_ADDRESS); 
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);
}

void loop() {

}

void requestEvents()
{
  SerialUSB.println(F("Recieved request"));
  Wire.write("I2C: Rover Lora Test");  // sends bytes
}

void receiveEvents(int numBytes)
{  

}
