#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>

#include "Controller.hpp"

Joystick_ joystick(0x03, JOYSTICK_TYPE_JOYSTICK,
    3, 0, // button, hat switch
    false, false, false, // x, y, z
    false, false, false, // rx, ry, rz
    false, false, // rudder, throttle
    false, false, false); // accelerator, brake, steering

ButtonData buttons[] = {
    ButtonData{0, 0},
    ButtonData{1, 1},
    ButtonData{2, 2},
    ButtonData{-1, 0}
};

void setup() {
    initializeButtons(buttons);
}

void loop() {
    processButtons(joystick, buttons);
    joystick.sendState();
}
