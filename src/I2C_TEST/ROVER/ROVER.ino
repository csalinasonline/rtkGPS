// Desc: Base
// Board: Sparkfun Artemis Thing Plus

#define I2C_LORA_ADDRESS  4

#include <Wire.h> //Needed for I2C to GPS

int RADIO_RDY_PIN = 4;

int len_pkt;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println("Serial: Rover Lora Test");

  pinMode(RADIO_RDY_PIN, INPUT);
  
  Wire.setClock(400000); //Increase I2C clock speed to 400kHz
  Wire.begin();
}

void loop() {
  if(digitalRead(RADIO_RDY_PIN)) {
    // Request pkt len from to slave
    Wire.requestFrom(I2C_LORA_ADDRESS, 20,0);  
    int i = 0;   
    while (Wire.available()) {
      if( i == 0 ) {
          len_pkt = Wire.read();
          Serial.println(len_pkt);
      }
      else {
        for( int j = 0; j < len_pkt -1; j++ ) {
          uint8_t c = Wire.read();
          Serial.write(c);
        }
        break;
      }
      i++;
   }
   Serial.println();
  }
}
