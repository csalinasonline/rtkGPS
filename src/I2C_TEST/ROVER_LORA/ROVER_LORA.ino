#define I2C_ROVER_ADDRESS  4

#include <Wire.h> //Needed for I2C to GPS

void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB)
    ; //Wait for user to open terminal
  SerialUSB.println("Serial: Lora Test");
  
  Wire.begin(); 
}

void loop() {
  SerialUSB.println("Sent i2c message to slave");
  Wire.beginTransmission(I2C_ROVER_ADDRESS); // transmit to device I2C_ROVER_ADDRESS
  Wire.write("I2C: Rover Lora Test");  // sends bytes
  Wire.endTransmission();    // stop transmitting
  delay(1000);
}
