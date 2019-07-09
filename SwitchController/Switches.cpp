/**
   Code to handle button presses.
*/

#include <Arduino.h>

#define DEFAULT_LONGPRESS_LEN    25  // Min nr of loops for a long press
#define DELAY                    20  // Delay per loop in ms

enum class SwitchStatus {
  NO_CHANGE_OFF,
  NO_CHANGE_ON,
  CHANGE_OFF,
  CHANGE_ON
};

class SwitchHandler {
  public:
    SwitchHandler(int pinIn): pin(pinIn) {

    }

    // Initialization done after construction, to permit static instances
    void init() {
      pinMode(pin, INPUT);
      digitalWrite(pin, HIGH); // pull-up
      was_pressed = false;
    }

    // Handler, to be called in the loop()
    SwitchStatus handle() {
      int event;
      boolean now_pressed = digitalRead(pin);

      if (was_pressed) {
        if (now_pressed) {
          return SwitchStatus::NO_CHANGE_ON;
        } else {
          was_pressed = false;
          return SwitchStatus::CHANGE_OFF;
        }
      } else {
        if (now_pressed) {
          was_pressed = true;
          return SwitchStatus::CHANGE_ON;
        } else {
          return SwitchStatus::NO_CHANGE_OFF;
        }
      }
    }

  protected:
    boolean was_pressed;     // previous state
    const int pin;           // pin to which button is connected
};
