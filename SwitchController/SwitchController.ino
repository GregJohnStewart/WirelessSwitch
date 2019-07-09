/*
   This code is what sends the signal to flip the switch.

   Components:
     - power LED
     - status LED
     - toggle switch
     - "send off" button

   When run:
     - listens for signal that switch activated and local switch flipped
     - turns on power LED
     - When switch flipped On:
       - sends signal to reciever to activate the switch
       - lights up status LED half/ yellow
     - When recieved ON confirmation:
       - lights up status LED full/ red
     - When switch flipped off or off button hit:
       - sends signal to reciever to turn off switch
       - lights up status LED half/yellow
     - When recieved OFF confirmation/ 5 secs after last ON confirmation:
       - turns off status LED

   By Greg Stewart
   Created 6/3/19
*/
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
   Constants for buttons
*/
#define eSwitchPin 4
#define sendOffButtonPin 3

/*
   Constants for status LED
*/
#define offConfirmed LedColorChoice::OFF
#define waitForConfirm LedColorChoice::YELLOW
#define onConfirmed LedColorChoice::RED

enum State {
  WAITING,
  ON_SENT,
  ON_CONFIRMED,
  OFF_SENT
};

LedHandler readyLed(readyLedPin);
RGBLedHandler statusLed(statusLedRPin, statusLedGPin, statusLedBPin);

TranscieverHandler transHand(txPin, rxPin, setPin, baudRate);
SwitchHandler eSwitch(eSwitchPin);
ButtonHandler sendOffButton(sendOffButtonPin);

State currentState = State::WAITING;
TransReadStatus lastStatus = TransReadStatus::NO_DATA;
SwitchStatus eSwitchStatus = SwitchStatus::NO_CHANGE_OFF;
ButtonStatus sendOffStatus = ButtonStatus::NO_CHANGE_OFF;

void setup() {
  Serial.begin(baudRate);

  // init buttons pins; I suppose it's best to do here
  eSwitch.init();
  sendOffButton.init();
  readyLed.init();
  statusLed.init();
  transHand.init();

  readyLed.turnOn();
  Serial.write("Initialized\n");
}

void loop() {
  Serial.write("Start of Loop\n");
  eSwitchStatus = eSwitch.handle();
  sendOffStatus = sendOffButton.handle();
  lastStatus = transHand.getLastRecievedStatus();

  if (currentState == State::WAITING) {
    Serial.write("\tIn Waiting state\n");
    if (eSwitchStatus == SwitchStatus::CHANGE_ON) {
      Serial.write("\tSwitch switched on. Sending on signal.\n");
      transHand.sendOn();
      statusLed.switchLed(waitForConfirm);
      currentState = State::ON_SENT;
    } else if (sendOffStatus == ButtonStatus::CHANGE_ON) {
      Serial.write("\tSend Off button set to on, sending off signal.\n");
      transHand.sendOff();
      statusLed.switchLed(waitForConfirm);
      currentState = State::OFF_SENT;
    }
  } else if (currentState == State::ON_SENT) {
    Serial.write("\tIn on_sent state\n");
    if (lastStatus == TransReadStatus::RELAY_ON) {
      Serial.write("\tGot signal that confirmed relay is on\n");
      currentState = State::ON_CONFIRMED;
      statusLed.switchLed(onConfirmed);
    } else if (eSwitchStatus == SwitchStatus::NO_CHANGE_ON) {
      Serial.write("\tNo change, still waiting for confirmation.\n");
      transHand.sendOn();
    } else if (eSwitchStatus == SwitchStatus::CHANGE_OFF || eSwitchStatus == SwitchStatus::NO_CHANGE_OFF) {
      Serial.write("\tSwitch changed to off before confirmation. Cancelling.\n");
      currentState = State::OFF_SENT;
      transHand.sendOff();
    }
  } else if (currentState == State::ON_CONFIRMED) {
    Serial.write("\tIn on_confirmed state\n");
    if (lastStatus == TransReadStatus::RELAY_OFF) {
      Serial.write("\tRelay has been switched off. From another source.\n");
      statusLed.switchLed(offConfirmed);
      currentState = State::WAITING;
    } else if (eSwitchStatus == SwitchStatus::CHANGE_OFF || eSwitchStatus == SwitchStatus::NO_CHANGE_OFF){
      Serial.write("\tSet to turn off relay.\n");
      currentState = State::OFF_SENT;
      transHand.sendOff();
      statusLed.switchLed(waitForConfirm);
    }
  }else if (currentState == State::OFF_SENT){
    Serial.write("\tIn off_sent state\n");
    if(lastStatus == TransReadStatus::RELAY_OFF) {
      Serial.write("\tGot confirmation that relay is off\n");
      currentState = State::WAITING;
      statusLed.switchLed(offConfirmed);
    } else if(sendOffStatus == ButtonStatus::CHANGE_ON){
      Serial.write("\tResending off signal\n");
      transHand.sendOff();
    }
  }
  delay(250);
}
