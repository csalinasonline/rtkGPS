#include <SPI.h>
#include <Wire.h>
//Radio Head Library: 
#include <RH_RF95.h>

#define I2C_LORA_ADDRESS  4

// We need to provide the RFM95 module's chip select and interrupt pins to the 
// rf95 instance below.On the SparkFun ProRF those pins are 12 and 6 respectively.
RH_RF95 rf95(12, 6);

int LED = 13; //Status LED on pin 13

int packetCounter = 0; //Counts the number of packets sent
long timeSinceLastPacket = 0; //Tracks the time stamp of last packet received
// The broadcast frequency is set to 921.2, but the SADM21 ProRf operates
// anywhere in the range of 902-928MHz in the Americas.
// Europe operates in the frequencies 863-870, center frequency at 
// 868MHz.This works but it is unknown how well the radio configures to this frequency:
//float frequency = 864.1;
float frequency = 921.2;

void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB)
    ; //Wait for user to open terminal
  SerialUSB.println("Serial: Lora Test");

  //Initialize the Radio. 
  if (rf95.init() == false){
    SerialUSB.println("Radio Init Failed - Freezing");
    while (1);
  }
  else{
  // An LED indicator to let us know radio initialization has completed.
    SerialUSB.println("Receiver up!");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  
  rf95.setFrequency(frequency); 
    
  Wire.setClock(400000); //Increase I2C clock speed to 400kHz
  Wire.begin(I2C_LORA_ADDRESS); 
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);
}

void loop() {
  if (rf95.available()) { //Read the availabe message 
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; 
  uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) { //Receive the message 
      digitalWrite(LED, HIGH); 
      //RH_RF95::printBuffer("Received: ", buf, len); 
      SerialUSB.print("Got: "); 
      SerialUSB.println((char*)buf);
      // Send a reply 
      uint8_t data[] = "Ack"; 
      rf95.send(data, sizeof(data)); 
      rf95.waitPacketSent(); 
      SerialUSB.println("Sent a reply"); 
      digitalWrite(LED, LOW); 
    } // If 2 end
    else { //If receive failed 
      SerialUSB.println("Receive failed"); 
    }  // Else 2 end
  }   // If 1 End
}

void requestEvents()
{
  SerialUSB.println(F("Recieved request"));
  Wire.write("I2C: Rover Lora Test");  // sends bytes
}

void receiveEvents(int numBytes)
{  

}
