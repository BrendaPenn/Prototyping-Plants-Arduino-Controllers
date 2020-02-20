// Referenced: https://www.arduino.cc/en/Tutorial/StateChangeDetection
// Prototyping Controller for the Sun 

#include <Keyboard.h>
    
const int  buttonPin = 6;    // the pin that the pushbutton is attached to the pin that the LED is attached to
// Variables will change:
int counter = 1;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:

  // initialize serial communication:
  Serial.begin(9600);
  Keyboard.begin();                                     
}
void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      Keyboard.press('+');
      // if the current state is HIGH then the button
      // went from off to on:
      counter++;
      Serial.println(counter);
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    Keyboard.releaseAll();
  }
  // save the current state as the last state for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED after two button pushes
//  if (counter >= 1) {
//    digitalWrite(ledPin, HIGH);
//    counter = 0;
//  }

}
