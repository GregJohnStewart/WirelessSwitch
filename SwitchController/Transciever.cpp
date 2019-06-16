/*
   This code controls the HC-12 transciever
*/
#include <Arduino.h>
#include <SoftwareSerial.h>

// for communicating with HC-12
#define txPin 10
#define rxPin 11
#define setPin 12
#define baudRate 9600
/*
 * Constants for signals
 */
#define setOnBytes String("SET RELAY ON")
#define setOffBytes String("SET RELAY OFF")
#define onBytes String("STATUS: RELAY IS ON")
#define offBytes String("STATUS: RELAY IS OFF")

SoftwareSerial HC12(txPin, rxPin);

enum class TransReadStatus {
  RELAY_OFF,
  RELAY_ON,
  NO_DATA
};

byte incomingByte;
String readBuffer = "";
TransReadStatus lastStatus = TransReadStatus::NO_DATA;
unsigned long lastSendOnSignal = millis();


void setupTransciever() {
  HC12.begin(baudRate);
  pinMode(setPin, OUTPUT);
  digitalWrite(setPin, HIGH);  // HC-12 normal, transparent mode
}

TransReadStatus checkForSignal() {
  while (HC12.available()) {             // If HC-12 has data
    incomingByte = HC12.read();          // Store each icoming byte from HC-12
    readBuffer += char(incomingByte);    // Add each byte to ReadBuffer string variable
  }
  delay(100);

  if (onBytes.equals(readBuffer)) {
    return TransReadStatus::RELAY_ON;
  } else if (offBytes.equals(readBuffer)) {
    return TransReadStatus::RELAY_OFF;
  }
  return TransReadStatus::NO_DATA;
}

TransReadStatus getLastRecievedStatus() {
  TransReadStatus newStatus = checkForSignal();

  if (newStatus == TransReadStatus::NO_DATA){
    return lastStatus;
  }
  lastStatus = newStatus;
  return lastStatus;
}
