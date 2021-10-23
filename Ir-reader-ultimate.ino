//hahah
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

bool sniffed = false;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void sniff()
{
  highpulse = 0;
  lowpulse = 0;

  while(FastReadDigitalPin(IRpin) != 0) //high
  {
    
    highpulse++;
    delayMicroseconds(RESOLUTION);

    if ((highpulse >= MAXPULSE)  && (pulseIndex != 0)) {
      printpulses();
      pulseIndex = 0;
      return;
    }
  }
  
  pulses[pulseIndex][HIGH_INDEX] = highpulse;

  

   while(FastReadDigitalPin(IRpin) == 0) //low
  {
    lowpulse++;
    delayMicroseconds(RESOLUTION);

    if ((lowpulse >= MAXPULSE)  && (pulseIndex != 0)) {
      printpulses();
      pulseIndex = 0;
      return;
    }
    
  }
  
  pulses[pulseIndex][LOW_INDEX] = lowpulse;

  pulseIndex++;
}

void loop(void)
{
 sniff();
}

void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < pulseIndex; i++) {
    Serial.print(pulses[i][LOW_INDEX] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][HIGH_INDEX] * RESOLUTION, DEC);
    Serial.println(" usec");
    sniffed = true;
  }
}

 uint16_t FastReadDigitalPin(uint16_t pin)
 {
  return  (IRpin_PIN & (1 << pin));
 }
