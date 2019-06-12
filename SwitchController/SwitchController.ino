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

#define baudRate 9600

// for communicating with HC-12
#define txPin 10
#define rxPin 11
#define setPin 12

// For other functionality
#define readyLed 8 // switched ON when setup is complete and ready to recieve
#define statusLedR 7 // LED to indicate status of switch
#define statusLedG 6 // LED to indicate status of switch
#define statusLedB 5 // LED to indicate status of switch

/*
 * Constants for signals
 */
#define onBytes String("SET RELAY ON")
#define offBytes String("RELAY OFF")

/*
 * Constants for buttons
 */
#define BUTTON1_PIN               2  // Button 1
#define BUTTON2_PIN               3  // Button 2

#define DEFAULT_LONGPRESS_LEN    25  // Min nr of loops for a long press
#define DELAY                    20  // Delay per loop in ms


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
