#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CHANNEL 5

RF24 radio(0, 1); // CE, CSN

#define BTN_PIN 2

// data transmittion packet
byte t_data = 5;

// transmitting and receiving address
const byte address[6] = "23571";

void setup()
{
  // setup button
  pinMode(BTN_PIN, INPUT);
  digitalWrite(BTN_PIN, INPUT_PULLUP); // Pull up the button pin

  // setup transmitter
  radio.begin();
  radio.setChannel(CHANNEL);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(address);
}

void loop()
{
  // monitor button
  if(!digitalRead(BTN_PIN))
    radio.write(&t_data, sizeof(t_data));
  
  delay(100);
}
