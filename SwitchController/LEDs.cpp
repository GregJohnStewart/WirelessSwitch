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
  WHITE = (RED & GREEN & BLUE),
  YELLOW = (RED & GREEN),
  LIGHT_BLUE = (BLUE & GREEN),
  MAGENTA = (BLUE & RED),
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

    void switchLed(int stateChoices){
      if(stateChoices | (int)LedColorChoice::RED){
        digitalWrite(rPin, LOW);
      } else {
        digitalWrite(rPin, HIGH);
      }
      if(stateChoices | (int)LedColorChoice::GREEN){
        digitalWrite(gPin, LOW);
      } else {
        digitalWrite(gPin, HIGH);
      }
      if(stateChoices | (int)LedColorChoice::BLUE){
        digitalWrite(bPin, LOW);
      } else {
        digitalWrite(bPin, HIGH);
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
