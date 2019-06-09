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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
