#define I2C_LORA_ADDRESS  4

#include <Wire.h> //Needed for I2C to GPS

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println("Serial: Rover Lora Test");

  Wire.setClock(400000); //Increase I2C clock speed to 400kHz
  Wire.begin();
}

void loop() {
  //Request value of n to slave
  Wire.requestFrom(I2C_LORA_ADDRESS, 20);
  while (Wire.available()) {
    uint8_t c = Wire.read();
    Serial.write(c);
  }
  Serial.println();
  delay(1000);
}
