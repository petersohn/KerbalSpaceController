#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>

#include "Controller.hpp"

Joystick_ joystick(0x04, JOYSTICK_TYPE_JOYSTICK,
    3, 0, // button, hat switch
    true, true, true, // x, y, z
    true, true, true, // rx, ry, rz
    false, false, // rudder, throttle
    false, false, false); // accelerator, brake, steering

ButtonData buttons[] = {
    ButtonData{0, 2},
    ButtonData{1, 1},
    ButtonData{2, 0},
    ButtonData{-1, 0}
};

AxisData axes[] = {
    AxisData{A0, &Joystick_::setZAxis},
    AxisData{A1, &Joystick_::setYAxis},
    AxisData{A2, &Joystick_::setXAxis},
    AxisData{A3, &Joystick_::setRzAxis},
    AxisData{A4, &Joystick_::setRyAxis},
    AxisData{A5, &Joystick_::setRxAxis},
    AxisData{-1, nullptr}
};

void setup() {
    initializeButtons(buttons);
    initializeAxes(axes);
}

void loop() {
    processButtons(joystick, buttons);
    processAxes(joystick, axes);
    joystick.sendState();
}

