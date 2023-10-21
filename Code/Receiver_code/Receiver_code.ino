#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define BUZZ_FREQ 4000 // buzzer output frequency
#define BUZZ_PIN  2
#define CHANNEL   5

RF24 radio(0, 1); // CE, CSN

// buzz function
void buzz(uint8_t duration);

// data reception packet
uint8_t r_data;

// transmitting and receiving address
const byte address[6] = "23571";

void setup()
{
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  // start up buzz
  while(!radio.begin())
    buzz(3);

  // setup receiver
  radio.begin();
  radio.setChannel(CHANNEL);  // Transmitter must be on the same channel
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop()
{
  if(radio.available())
    radio.read(&r_data, sizeof(r_data));

  if(r_data)
    buzz(1);

   r_data = 0;
}

void buzz(uint8_t duration)
{
  unsigned long init_time = millis();
  unsigned long del = (1/BUZZ_FREQ) * 500;
  while(millis() - init_time < duration * 100)
  {
    digitalWrite(BUZZ_PIN, HIGH);
    delay(del);
    digitalWrite(BUZZ_PIN, LOW);
    delay(del);
  }
}
