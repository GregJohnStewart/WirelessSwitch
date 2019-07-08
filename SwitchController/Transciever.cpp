/*
   This code controls the HC-12 transciever
*/
#include <Arduino.h>
#include <SoftwareSerial.h>

enum class TransReadStatus {
  RELAY_OFF,
  RELAY_ON,
  NO_DATA
};

class TranscieverHandler {
  public:
    TranscieverHandler(
      int txPinIn,
      int rxPinIn,
      int setPinIn,
      int baudRateIn
    ): txPin(txPinIn),
      rxPin(rxPinIn),
      setPin(setPinIn),
      baudRate(baudRateIn),
      hc12(txPin, rxPin)
    {
      //nothing to do
    }

    void init() {
      hc12.begin(baudRate);
      pinMode(setPin, OUTPUT);
      digitalWrite(setPin, HIGH);  // HC-12 normal, transparent mode
    }


    TransReadStatus checkForSignal() {
      while (hc12.available()) {             // If HC-12 has data
        incomingByte = hc12.read();          // Store each icoming byte from HC-12
        readBuffer += char(incomingByte);    // Add each byte to ReadBuffer string variable
      }
      delay(100);

      if (onBytes.equals(readBuffer)) {
        readBuffer = "";
        return TransReadStatus::RELAY_ON;
      } else if (offBytes.equals(readBuffer)) {
        readBuffer = "";
        return TransReadStatus::RELAY_OFF;
      }
      readBuffer = "";
      return TransReadStatus::NO_DATA;
    }

    TransReadStatus getLastRecievedStatus() {
      TransReadStatus newStatus = checkForSignal();

      if (newStatus == TransReadStatus::NO_DATA) {
        return lastStatus;
      }
      lastStatus = newStatus;
      return lastStatus;
    }

    void sendOff(){
      hc12.write(setOffBytes.c_str());
    }

    void sendOn(){
      unsigned long current = millis();
      unsigned long difference = current - lastSendOnSignal;
      if (difference <= sendOnDelay) {
        lastSendOnSignal = current;
        hc12.write(onBytes.c_str());
        delay(100);
      }
    }
    
  protected:
    const int txPin;// = 10;
    const int rxPin;// = 11;
    const int setPin;// = 12;
    const int baudRate;// 9600
    /*
       Constants for signals
    */
    const String setOnBytes = String("SET RELAY ON");
    const String setOffBytes = String("SET RELAY OFF");
    const String onBytes = String("STATUS: RELAY IS ON");
    const String offBytes = String("STATUS: RELAY IS OFF");
    const int sendOnDelay = 500;//half a second

    const SoftwareSerial hc12;

    byte incomingByte;
    String readBuffer = "";
    TransReadStatus lastStatus = TransReadStatus::NO_DATA;
    unsigned long lastSendOnSignal = millis();
};
