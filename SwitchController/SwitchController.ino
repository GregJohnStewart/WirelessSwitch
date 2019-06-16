/*
 * This code is what sends the signal to flip the switch.
 * 
 * Components:
 *   - power LED
 *   - status LED
 *   - toggle switch
 *   - "send off" button
 * 
 * When run:
 *   - Sets relay to OFF
 *   - listens for signal that switch activated and local switch flipped
 *   - turns on power LED
 *   - When switch flipped On:
 *     - sends signal to reciever to activate the switch
 *     - lights up status LED half/ yellow
 *   - When recieved ON confirmation:
 *     - lights up status LED full/ red
 *   - When switch flipped off or off button hit:
 *     - sends signal to reciever to turn off switch
 *     - lights up status LED half/yellow
 *   - When recieved OFF confirmation/ 5 secs after last ON confirmation:
 *     - turns off status LED
 *     
 * By Greg Stewart
 * Created 6/3/19
 */

#include <SoftwareSerial.h>
#include "Buttons.cpp"
#include "Switches.cpp"
#include "Transciever.cpp"
#include "LEDs.cpp"

#define baudRate 9600


// For other functionality
#define readyLedPin 8 // switched ON when setup is complete and ready to recieve
#define statusLedRPin 7 // LED to indicate status of switch
#define statusLedGPin 6 // LED to indicate status of switch
#define statusLedBPin 5 // LED to indicate status of switch


/*
 * Constants for buttons
 */
#define eSwitchPin 4
#define sendOffButtonPin 3


enum ActionState{
  WAITING,
  SEND_ON_SIGNAL,
  SEND_OFF_SIGNAL
};

ButtonHandler eSwitch(eSwitchPin);
SwitchHandler sendOffButton(sendOffButtonPin);
LedHandler readyLed(readyLedPin);
RGBLedHandler statusLed(statusLedRPin, statusLedGPin, statusLedBPin);


void setup() {
  Serial.begin(baudRate);

  // init buttons pins; I suppose it's best to do here
  eSwitch.init();
  sendOffButton.init();
  readyLed.init();
  statusLed.init();
  setupTransciever();

  readyLed.turnOn();
}

void loop() {
  // put your main code here, to run repeatedly:

}
