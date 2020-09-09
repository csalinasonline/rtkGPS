 #include <SPI.h>

//Radio Head Library: 
#include <RH_RF95.h>

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

void setup()
{
  pinMode(LED, OUTPUT);

  Serial1.begin(115200);
  Serial1.setTimeout(2000);
  // It may be difficult to read serial messages on startup. The following
  // line will wait for serial to be ready before continuing. Comment out if not needed.
  while(!Serial1);
  Serial1.println("RFM Server!");

  //Initialize the Radio. 
  if (rf95.init() == false){
    Serial1.println("Radio Init Failed - Freezing");
    while (1);
  }
  else{
  // An LED indicator to let us know radio initialization has completed.
    Serial1.println("Receiver up!");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  rf95.setFrequency(frequency); 

 // The default transmitter power is 13dBm, using PA_BOOST.
 // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
 // you can set transmitter powers from 5 to 23 dBm:
 // rf95.setTxPower(14, false);
}

void loop()
{
  // Should be a message for us now
  uint8_t buf[400];
  uint8_t buf2[10];
  uint8_t len = sizeof(buf);

  // Send a reply
  uint8_t toSend;
  if (Serial1.available()) {      // If anything comes in Serial (USB),
   int data_len = Serial1.readBytes(buf, len);   // read it and send it out Serial1 (pins 0 & 1)
   
   if ( data_len < 3) {
     buf[data_len] = 0xaa;
     rf95.send(buf, data_len + 1);
     rf95.waitPacketSent();   
   }
   else {
     memcpy(buf2, buf, 3);
     buf2[3] = 0xbb;
     rf95.send(buf2, 3 + 1);
     rf95.waitPacketSent();  

     memcpy(buf2, buf + 3, data_len - 3);
     buf2[data_len - 3] = 0xcc;
     rf95.send(buf2, data_len - 3 + 1);
     rf95.waitPacketSent();  
   } 

  }
}
