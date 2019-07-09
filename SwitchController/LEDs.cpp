#include <Arduino.h>

class LedHandler {
  public:
    LedHandler(int pinIn): pin(pinIn){
      
    }

    void init() {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    void switchLed(boolean newState){
      if(newState){
        digitalWrite(pin, HIGH);
      } else {
        digitalWrite(pin, LOW);
      }
    }

    void turnOn(){
      switchLed(true);
    }

    void turnOff(){
      switchLed(false);
    }
    

  protected:
    const int pin;           // pin to which button is connected
};

enum class LedColorChoice {
  OFF = 0,
  RED = 1,
  GREEN = 2,
  BLUE = 4,
  WHITE = (RED | GREEN | BLUE),
  YELLOW = (RED | GREEN),
  LIGHT_BLUE = (BLUE | GREEN),
  MAGENTA = (BLUE | RED),
};

class RGBLedHandler {
  public:
    RGBLedHandler(
      int rPinIn,
      int gPinIn,
      int bPinIn
    ):rPin(rPinIn),
      gPin(gPinIn),
      bPin(bPinIn)
    {
      
    }

    void init() {
      pinMode(rPin, OUTPUT);
      pinMode(gPin, OUTPUT);
      pinMode(bPin, OUTPUT);
      digitalWrite(rPin, LOW);
      digitalWrite(gPin, LOW);
      digitalWrite(bPin, LOW);
    }

    void switchLed(LedColorChoice stateChoice){
      this->switchLed((int)stateChoice);
    }

    void switchLed(int stateChoices){
      if((stateChoices & (int)LedColorChoice::RED) != 0){
        digitalWrite(rPin, HIGH);
      } else {
        digitalWrite(rPin, LOW);
      }
      if((stateChoices & (int)LedColorChoice::GREEN) != 0){
        digitalWrite(gPin, HIGH);
      } else {
        digitalWrite(gPin, LOW);
      }
      if((stateChoices & (int)LedColorChoice::BLUE) != 0){
        digitalWrite(bPin, HIGH);
      } else {
        digitalWrite(bPin, LOW);
      }
    }

    void turnOff(){
      switchLed(0);
    }
    
  protected:
    const int rPin;
    const int gPin;
    const int bPin;
};
