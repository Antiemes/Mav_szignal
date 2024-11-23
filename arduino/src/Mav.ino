#include "TimerOne.h"

#define SOUND_PIN 8
#define BUTTON_PIN 12
#define LED_PIN 13

const uint16_t notes[][2]={
                     {1175,  0},
                     {1175,  0},
                     { 880,  0},
                     { 987,  0},
                     { 880,  0},
                     { 880,  0},
                     {1175,740},
                     {1175,784},
                     { 880,740},
                     { 880,740},
                     { 880,740},
                     {   0,  0},
};

uint32_t dds1=0, dds2=0;
uint8_t i=0;
uint32_t j=0;

void dds()
{
  uint8_t x;
  dds1+=notes[i][0]*134213;
  dds2+=notes[i][1]*134213;
  x=(dds1>>31)|(dds2>>31);
  digitalWrite(SOUND_PIN, x);
  j++;
  if (j==5764)
  {
    j=0;
    i++;
    if (notes[i][0]==0)
    {
      Timer1.detachInterrupt();
    }
  }
}

void start_chime()
{
  dds1=0;
  dds2=0;
  i=0;
  j=0;
  Timer1.attachInterrupt(dds);
}

void setup()
{
	pinMode(SOUND_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, 0);

  Timer1.initialize(31);
}

void loop()
{
  while(!digitalRead(BUTTON_PIN));
  delay(200);
  while(digitalRead(BUTTON_PIN));
  start_chime();
}

