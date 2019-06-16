/*
   This code controls the HC-12 transciever
*/
SoftwareSerial HC12(txPin, rxPin);
byte incomingByte;
String readBuffer = "";
unsigned long lastSendOnSignal = millis();

void setupTransciever() {
  HC12.begin(baudRate);
  pinMode(setPin, OUTPUT);
  digitalWrite(setPin, HIGH);  // HC-12 normal, transparent mode
}

void checkForSignal() {
  while (HC12.available()) {             // If HC-12 has data
    incomingByte = HC12.read();          // Store each icoming byte from HC-12
    readBuffer += char(incomingByte);    // Add each byte to ReadBuffer string variable
  }

  if (setOnBytes.equals(readBuffer)) {
    signalOn = true;
  } else if (setOffBytes.equals(readBuffer)) {
    signalOn = false;
  }
  delay(100);
}

void sendOnConfirm() {
  unsigned long current = millis();
  unsigned long difference = current - lastSendOnSignal;

  if (difference <= sendStatusDelay) {
    lastSendOnSignal = current;
    if (signalOn) {
      HC12.write(onBytes.c_str());
    } else {
      HC12.write(offBytes.c_str());
    }
    delay(100);
  }
}

void doTransciever() {
  checkForSignal();
  sendOnConfirm();
}
