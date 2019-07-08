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

// #include <SoftwareSerial.h>
#include "Buttons.cpp"
#include "Switches.cpp"
#include "Transciever.cpp"
#include "LEDs.cpp"

#define baudRate 9600

// for communicating with HC-12
#define txPin 10
#define rxPin 11
#define setPin 12


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

/*
 * Constants for status LED
 */
#define offConfirmed LedColorChoice::OFF
#define waitForConfirm LedColorChoice::YELLOW
#define onConfirmed LedColorChoice::RED


enum ActionState{
  WAITING,
  SEND_ON_SIGNAL,
  SEND_OFF_SIGNAL
};

LedHandler readyLed(readyLedPin);
RGBLedHandler statusLed(statusLedRPin, statusLedGPin, statusLedBPin);

TranscieverHandler transHand(txPin, rxPin, setPin, baudRate);
SwitchHandler eSwitch(eSwitchPin);
ButtonHandler sendOffButton(sendOffButtonPin);



ActionState state = WAITING;

void setup() {
  Serial.begin(baudRate);

  // init buttons pins; I suppose it's best to do here
  eSwitch.init();
  sendOffButton.init();
  readyLed.init();
  statusLed.init();
  transHand.init();

  readyLed.turnOn();
}

void loop() {
  // do actions for set state



  // read in data
  
  
}
