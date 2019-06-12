/*
 * This code is what runs the actual relay based on what it recieves from the wireless transponder.
 * 
 * Components:
 *   - Relay switch
 *   - power LED
 *   - status LED
 * 
 * When run:
 *   - Sets relay to OFF
 *   - listens for signal to switch on
 *   - turns on power LED
 *   - When recieves signal to switch:
 *     - Switches relay on
 *     - Turns on status LED
 *   - While switch is "ON":
 *     - periodically send out "ON" confirmation signal
 *   - While switch is "OFF":
 *     - periodically send out "OFF" confirmation signal
 *   - When recieves signal to switch off:
 *     - Switches relay off
 *     - Turns off status LED
 * 
 * 
 * 
 * By Greg Stewart
 * Created 6/3/19
 */

#include <SoftwareSerial.h>

#define baudRate 9600

// for communicating with HC-12
#define txPin 10
#define rxPin 11
#define setPin 12
#define sendOnDelay 2000

//for switching the relay
#define relayPin 13

// For other functionality
#define readyLed 8 // switched ON when setup is complete and ready to recieve
#define statusLed 7 // LED to indicate status of switch

/*
 * Constants for signals
 */
#define onBytes String("SET RELAY ON")
#define offBytes String("RELAY OFF")

boolean signalOn = false;

void setup() {
  //setup serial ports
  Serial.begin(baudRate);
  setupRelay();
  setupTransciever();
  
  pinMode(readyLed, OUTPUT);
  digitalWrite(readyLed, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  doRelay();
  doTransciever();
}
