/*
   This code controls the Relay
*/

/*
   Sets up the relay for use.
*/
void setupRelay() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, LOW);
}

/*
   Turns on/off the relay based on the 'relayStatus' variable.
*/
void doRelay() {
  if (signalOn) {
    Serial.write("\tRelay set to ON\n");
    digitalWrite(relayPin, LOW);
    digitalWrite(statusLed, HIGH);
  } else {
    Serial.write("\tRelay set to OFF\n");
    digitalWrite(relayPin, HIGH);
    digitalWrite(statusLed, LOW);
  }
}
