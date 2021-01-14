#define IRpin_PIN      PIND
#define IRpin          2
#define MAXPULSE 65000
 
#define RESOLUTION 20 

#define HIGH_INDEX 1
#define LOW_INDEX 0

uint16_t pulses[100][2];
uint8_t pulseIndex = 0;
uint16_t highpulse = 0;
uint16_t lowpulse = 0;

bool highState = false;
bool lowState = false;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void loop(void)
{
  if (FastReadDigitalPin(IRpin))
  {
    Serial.print(" :) ");
    highState = true;
    highpulse++;
    if (lowState)
    {
      pulses[pulseIndex][LOW_INDEX] = lowpulse;
      lowpulse = 0;
      lowState = false;
      Serial.print("Switch to High");
    }
  }
  else
  {
    Serial.print(" :( ");
    lowState = true;
    lowpulse++;
    if (highState)
    {
      pulses[pulseIndex][HIGH_INDEX] = highpulse;
      highpulse = 0;
      highState=false;
       Serial.print("Switch to Low");
    }
  }

  if ((lowpulse >= MAXPULSE)  && (pulseIndex != 0)) {
    printpulses();
    pulseIndex = 0;
    return;
  }

  if ((highpulse >= MAXPULSE)  && (pulseIndex != 0)) {
    printpulses();
    pulseIndex = 0;
    return;
  }

  pulseIndex++;
 
  delay(RESOLUTION);
}

void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < pulseIndex; i++) {
    Serial.print(pulses[i][LOW_INDEX] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][HIGH_INDEX] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
}

 uint16_t FastReadDigitalPin(uint16_t pin)
 {
  return  (IRpin_PIN & (1 << pin));
 }
