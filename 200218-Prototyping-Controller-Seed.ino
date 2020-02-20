/* For Prototyping Studio 2020 in the MHCI+D program at UW.
 *  Reference: https://github.com/jonfroehlich/arduino/blob/master/GameController/ButtonController/ButtonController.ino
 *  
 *  Converts digital input to keyboard input. Specifically, uses digital input on pins 
 *  3 and 5 for "d" to move right and "a" to move left respectively on the keyboard. 
 *  All digital input is assumed to use the Arduino's internal pull-up resistors
 *  
 * This sketch should work with any 32u4- or SAMD-based boards like the Arduino
 * Leondardo, Esplora, Zero, Due, which can appear as a native mouse and/or keyboard
 * when connected to the computer via USB.
 * 
 * References
 *  - https://www.arduino.cc/en/Reference.MouseKeyboard
 *  - https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardpress/
 *  - https://www.arduino.cc/en/Reference/KeyboardModifiers
 * 
 * By Jon Froehlich
 * @jonfroehlich
 * http://makeabilitylab.io
 */
#include <Keyboard.h>

const int BUTTON_RIGHT_PIN = 3;
const int BUTTON_LEFT_PIN = 5;
boolean isAPressed = false;
boolean isDPressed = false; 

void setup() {
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);

  // Turn on serial for debugging
  Serial.begin(9600); 
  Keyboard.begin();
}

void loop() {
  int buttonRightVal = digitalRead(BUTTON_RIGHT_PIN);
  int buttonLeftVal = digitalRead(BUTTON_LEFT_PIN);
  int numButtonsPressed = 0;

  // List of non-alphanumerica keys:
  //  - https://www.arduino.cc/en/Reference/KeyboardModifiers

  if(buttonRightVal == HIGH){
    isDPressed = true;
    Keyboard.press('d');
    Serial.print("RIGHT: Pressed\t");
    numButtonsPressed++;
  } else if(isDPressed == true && buttonLeftVal == LOW){
    Keyboard.release(' ');
    isDPressed = false;
  }

  if(buttonLeftVal == HIGH){
    isAPressed = true;
    Keyboard.press('a');
    Serial.print("LEFT: Pressed");
    numButtonsPressed++;
  } else if(isAPressed == true && buttonLeftVal == LOW){
    Keyboard.release(' ');
    isAPressed = false;
  }

  delay(50);
  Keyboard.releaseAll();

  if(numButtonsPressed > 0){
    Serial.println();
  }
}
