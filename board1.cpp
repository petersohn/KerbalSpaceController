#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>
#include <Keyboard.h>

#include "Controller.hpp"
#include "JoystickButtonController.hpp"

Joystick_ joystick(0x03, JOYSTICK_TYPE_JOYSTICK,
    15, 0, // button, hat switch
    true, true, false, // x, y, z
    false, false, false, // rx, ry, rz
    false, true, // rudder, throttle
    true, false, true); // accelerator, brake, steering

ButtonData buttons[] = {
    ButtonData{0, 0},
    ButtonData{1, 1},
    ButtonData{2, 2},
    ButtonData{3, 3},
    ButtonData{4, 4},
    ButtonData{5, 5},
    ButtonData{6, 6},
    ButtonData{7, 7},
    ButtonData{9, 8},
    ButtonData{10, 9},
    ButtonData{11, 10},
    ButtonData{13, 11},
    ButtonData{12, 12},
    ButtonData{-1, 0}
};

AxisData axes[] = {
    // AxisData{A1, &Joystick_::setYAxis},
    // AxisData{A2, &Joystick_::setXAxis},
    AxisData{A3, &Joystick_::setAccelerator},
    AxisData{A4, &Joystick_::setSteering},
    AxisData{A5, &Joystick_::setThrottle},
    AxisData{-1, nullptr}
};

int zoomButtons[] = {13, -1, 14, -2};

MultiButtonData multiButtons[] = {
    MultiButtonData{A0, -1, 0, 0, zoomButtons},
    MultiButtonData{-1, 0, 0, 0, nullptr}
};

void setup() {
    initializeButtons(buttons);
    initializeAxes(axes);
    initializeMultiButtons(multiButtons);
}

JoystickButtonController joystickButtonController{joystick};

void loop() {
    processButtons(joystickButtonController, buttons);
    processAxes(joystick, axes);
    processMultiButtons(joystickButtonController, multiButtons);
    joystick.sendState();
}
