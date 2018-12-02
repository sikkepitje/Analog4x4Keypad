/* 
 *  Analog4x4Keypad
 * 
 *  Bibliotheek voor analoge Button Keypad 4x4 met debouncing.
 * 
 *  https://www.vanallesenmeer.nl/Button-Keypad-4x4-module
 *  oftewel RobotDyn Keypad 4x4 matrix analog
 *  die is opgebouwd als 16 spanningsdelers. 
 *  naar het voorbeeld voor debouncing volgens 
 *  Arduino Bestand -> Voorbeelden -> Digital -> Debounce
 * 
 *  Paul Wiegmans
 *  2 dec 2018
 */

#include <Analog4x4Keypad.h>

const int analogKeyValues[16] = 
    {1023, 930, 850, 790, 680, 640, 600, 570, 
    512, 487, 465, 445, 410, 330, 277, 238};

AnalogKeypad::AnalogKeypad(uint8_t analogKeyPin) {
    _apin = analogKeyPin;
    _button = -1;
    _lastDebounceTime = 0;
}

int AnalogKeypad::_getAnalogKeypad() {
    int analogvalue = analogRead(_apin);
    for (int t = 0; t < 16; t++) {   
        int distance = analogvalue - analogKeyValues[t];
        if (abs(distance) < MAXDISTANCE) {
            return t;
        }
    }
    return -1;
}

char AnalogKeypad::_button2char(int button) {
    if (button >= 0) {
        return "0123456789abcdef"[button];
    } else {
        return 0;
    }
}

void AnalogKeypad::_getreading() {
    // read the state of the switch into a local variable:
    int reading = _getAnalogKeypad();
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != _lastButtonState) {
        // reset the debouncing timer
        _lastDebounceTime = millis();
    }
    if ((millis() - _lastDebounceTime) > DEBOUNCEDELAY) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != _buttonState) {
            _buttonState = reading;

            // only toggle the LED if the new button state is pressed
            if (_buttonState >= 0) {
                _button = reading;      // save for later reading
            }
        }
    }
    _lastButtonState = reading;
}

bool AnalogKeypad::buttonpressed() {   // non-blocking key press detected
    _getreading();
    return (_button >= 0);
}

int AnalogKeypad::getbutton() {     // blocking get button 
    while (_button < 0) {
        _getreading();
    }
    int button = _button;
    _button = -1;         // reset to not pressed
    return button;
}

char AnalogKeypad::getch() {        // blocking get key
  return _button2char(getbutton());
}

