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
 *     - Sends signal out to confirm
 *     - Turns on status LED
 *   - When recieves signal to switch off:
 *     - Switches relay off
 *     - sends out signal to confirm
 *     - Turns off status LED
 * 
 * 
 * 
 * 
 * By Greg Stewart
 * Created 6/3/19
 */

#include <SoftwareSerial.h>

#define txPin 10
#define rxPin 11

#define setPin 6
#define button1 4
#define button2 3

/* 
 * setup for transiever, read/writing
 */
SoftwareSerial HC12(txPin, rxPin);
byte incomingByte;
String readBuffer = "";


void setup() {
  //setup serial ports
  Serial.begin(9600);
  HC12.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}
