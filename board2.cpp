#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>

#include "Controller.hpp"

Joystick_ joystick(0x04, JOYSTICK_TYPE_JOYSTICK,
    22, 0, // button, hat switch
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

int walkerXButtons[] = {8, -1, 9, -2};
int walkerYButtons[] = {10, -1, 11, -2};
int sasButtons[] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, -2};

MultiButtonData multiButtons[] = {
    MultiButtonData{A7, -1, 0, 0, walkerXButtons},
    MultiButtonData{A6, -1, 0, 0, walkerYButtons},
    MultiButtonData{A8, 9, 0, 0, sasButtons},
    MultiButtonData{-1, 0, 0, 0, nullptr}
};

void setup() {
    initializeButtons(buttons);
    initializeAxes(axes);
    initializeMultiButtons(multiButtons);
    // Serial.begin(115200);
}

void loop() {
    // Serial.println("loop");
    processButtons(joystick, buttons);
    processAxes(joystick, axes);
    processMultiButtons(joystick, multiButtons);
    joystick.sendState();
}

