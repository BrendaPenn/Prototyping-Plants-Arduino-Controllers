/*
 *
 * Tap Detection:
 *  - Detects rate of tapping and outputs a keyboard press of 1, 2 or 3, depending on rate
 *
 */

#include <Keyboard.h>

const int DELAY = 50;
const int BTN_PIN = 8;
const unsigned int INT_MAX = 65535;   // 16-bit number, so max possible number is ((2^16) - 1)
const unsigned int THRESHOLD_01 = 5;  // 5  * DELAY =  250 ms
const unsigned int THRESHOLD_02 = 15; // 15 * DELAY =  750 ms
const unsigned int THRESHOLD_03 = 25; // 25 * DELAY = 1250 ms
boolean isRaining = false;
boolean is1Pressed = false; 
boolean is2Pressed = false; 
boolean is3Pressed = false; 

int currentStatus = 0;
int previousStatus = 0;

unsigned int counter = 0;

void setup() {
  pinMode(BTN_PIN, INPUT);
  Serial.begin(9600);
  Keyboard.begin();                                     
}

void loop() {
  currentStatus = digitalRead(BTN_PIN);
  
  // Check for positive edge
  if (currentStatus == HIGH && previousStatus == LOW)
  {
    if (counter <= THRESHOLD_01) 
    {
      //only write 1 to the keyboard once
      if(is1Pressed == false) {
        is1Pressed = true;
        is2Pressed = false;
        is3Pressed = false; 
        Keyboard.write('1');
      }
    }
    else if (counter <= THRESHOLD_02)
    {
      if(is2Pressed == false) {
          is1Pressed = false; 
          is2Pressed = true;
          is3Pressed = false; 
          Keyboard.write('2');
      }
    }
    else if (counter <= THRESHOLD_03)
    {
      if(is3Pressed == false) {
          is1Pressed = false;
          is2Pressed = false;
          is3Pressed = true;
          Keyboard.write('3');
      }
    }  
    
    isRaining = true;
    counter = 0;
  }

  if (isRaining == true && counter > 50) {
    isRaining = false;
    is1Pressed = false;
    is2Pressed = false; 
    is3Pressed = false; 
    Keyboard.write('0');
  }
  previousStatus = currentStatus;
  
  // NOTE: If counter was 'int' instead of 'unsinged int', we would have to make sure that 
  // .. the value of counter is less that the MAX of an int before incrementing. Otherwise,
  // .. we would cause an overflow and the number would become negative. 
  // .. The MAX int value is ((2^15)-1).
  counter++;

  delay(DELAY);  // Check every 50 ms  

  Keyboard.releaseAll();
}
