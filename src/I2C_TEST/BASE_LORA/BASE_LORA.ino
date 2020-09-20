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
  SerialUSB.println("Serial: Lora Radio Test");

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
    
  Wire.begin(I2C_LORA_ADDRESS); // transmit to device I2C_LORA_ADDRESS
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);
}

void loop() {
  char radiopacket[20]= "12345";
  SerialUSB.print("Sending "); 
  SerialUSB.println(radiopacket);
  rf95.send((uint8_t *) radiopacket, 20);
  rf95.waitPacketSent();
  
  // Waiting for the reply 
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; 
  uint8_t len = sizeof(buf);
    
  if (rf95.waitAvailableTimeout(1000)) {
  // Should be a reply message for us now 
    if (rf95.recv(buf, &len)) { 
      SerialUSB.print("Got reply: ");
      SerialUSB.println((char*)buf); 
      //  SerialUSB.print("RSSI: "); 
      //  SerialUSB.println(rf95.lastRssi(), DEC); 
    }  // If 2 end
    else { 
      SerialUSB.println("Receive failed"); 
    } // Else 2 end
  } // If 1 end
  else { 
    SerialUSB.println("No reply, is the receiver running?"); 
  }  // Else 1 end 
  delay(1000);
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
    if (rf95.available()){
      rf95.send(&c, sizeof(c));
      rf95.waitPacketSent();
    }
  }
  SerialUSB.println();
}
