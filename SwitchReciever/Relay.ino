/*
   This code controls the Relay
*/

/*
   Sets up the relay for use.
*/
void setupRelay() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, LOW);
}

/*
   Turns on/off the relay based on the 'relayStatus' variable.
*/
void doRelay() {
  if (signalOn) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(statusLed, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(statusLed, LOW);
  }
}
