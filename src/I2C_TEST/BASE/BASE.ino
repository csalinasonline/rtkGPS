// Desc: Base
// Board: Sparkfun RedBoard Artemis

#define I2C_LORA_ADDRESS  4

#include <Wire.h> //Needed for I2C to GPS

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println("Serial: Base Lora Test");
  
  Wire.begin(); 
}

void loop() {
  Serial.println("Sent i2c message to slave");
  Wire.beginTransmission(I2C_LORA_ADDRESS); // transmit to device I2C_LORA_ADDRESS
  Wire.write("1234567890");  // sends bytes
  Wire.endTransmission();    // stop transmitting
  delay(1000);
}
