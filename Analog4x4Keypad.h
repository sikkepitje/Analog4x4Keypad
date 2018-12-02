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

#ifndef AnalogKeypad_h
#define AnalogKeypad_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define MAXDISTANCE 18      /* maximum value difference to be detected as pressed key */
#define DEBOUNCEDELAY 50    /* key debounce delay (ms) */

class AnalogKeypad {
    private:
        char _apin;                 // analog pin connected to keypad
        int _buttonState;           // the current reading from the input pin
        int _lastButtonState = 0;   // the previous reading from the input pin
        unsigned long _lastDebounceTime = 0;  // the last time the output pin was toggled
        int _button = -1;

        int _getAnalogKeypad();     // get unfiltered button press value
        char _button2char(int button);  // translate button number to character
        void _getreading() ;
    public:
        AnalogKeypad(uint8_t analogKeyPin); // constructor
        bool buttonpressed();       // non-blocking key press detected
        char getch();               // get key blocking
        int getbutton();            // get button blocking
};

#endif
