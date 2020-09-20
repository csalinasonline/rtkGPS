#include <SPI.h>
#include <Wire.h>
//Radio Head Library: 
#include <RH_RF95.h>

#define I2C_SLAVE_ADDRESS 4

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

int buf_len;

void setup()
{
  pinMode(LED, OUTPUT);

  SerialUSB.begin(115200);
  SerialUSB.setTimeout(2000);
  // It may be difficult to read serial messages on startup. The following
  // line will wait for serial to be ready before continuing. Comment out if not needed.
  while(!SerialUSB);
  SerialUSB.println("RFM Server!");

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

  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);

 // The default transmitter power is 13dBm, using PA_BOOST.
 // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
 // you can set transmitter powers from 5 to 23 dBm:
 // rf95.setTxPower(14, false);
}

void loop()
{
//  // Should be a message for us now
//  uint8_t buf[400];
//  uint8_t len = sizeof(buf);
//
//   if ( buf_len < RH_RF95_MAX_MESSAGE_LEN) {
//     rf95.send(buf, RH_RF95_MAX_MESSAGE_LEN);
//     rf95.waitPacketSent();   
//     digitalWrite(LED, HIGH); 
//   }
}

void requestEvents()
{

}

void receiveEvents(int numBytes)
{  
  uint8_t c = Wire.read();
  buf_len = numBytes;
  SerialUSB.write(c);
}
