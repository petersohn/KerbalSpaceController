#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "ButtonPresser.hpp"
#include "Controller.hpp"

#include <Joystick.h>

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
    ButtonData{12, 12},
    ButtonData{13, 11},
    ButtonData{}
};

ButtonPresser throttleKiller{joystick, 12};

void postProcessThrottle(int value) {
    if (value == 0) {
        throttleKiller.press();
    }
}

AxisData axes[] = {
    AxisData{A1, &Joystick_::setYAxis},
    AxisData{A2, &Joystick_::setXAxis},
    AxisData{A3, &Joystick_::setAccelerator},
    AxisData{A4, &Joystick_::setSteering},
    AxisData{A5, &Joystick_::setThrottle, &postProcessThrottle},
    AxisData{}
};

int zoomButtons[] = {13, -1, 14, -2};

MultiButtonData multiButtons[] = {
    MultiButtonData{A0, -1, zoomButtons},
    MultiButtonData{}
};

void setup() {
    joystick.begin(false);
}

void loop() {
    processButtons(joystick, buttons);
    processAxes(joystick, axes);
    processMultiButtons(joystick, multiButtons);
    throttleKiller.update();
    joystick.sendState();
}
