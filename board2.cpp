#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>
#include <Keyboard.h>

#include "Controller.hpp"
#include "JoystickButtonController.hpp"
#include "KeyboardButtonController.hpp"

Joystick_ joystick(0x04, JOYSTICK_TYPE_JOYSTICK,
    14, 0, // button, hat switch
    true, true, true, // x, y, z
    true, true, true, // rx, ry, rz
    false, false, // rudder, throttle
    false, false, false); // accelerator, brake, steering

ButtonData keys[] = {
    ButtonData{3, KEY_ESC},
    ButtonData{7, KEY_F5},
    ButtonData{5, KEY_F9},
    ButtonData{-1, 0}
};

ButtonData buttons[] = {
    ButtonData{0, 0},
    ButtonData{1, 1},
    ButtonData{2, 2},
    ButtonData{13, 3},
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

int walkerXButtons[] = {'a', -1, 'd', -2};
int walkerYButtons[] = {'w', -1, 's', -2};
int sasButtons[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, -2};

MultiButtonData multiButtons[] = {
    MultiButtonData{A8, 9, 0, 0, sasButtons},
    MultiButtonData{-1, 0, 0, 0, nullptr}
};

MultiButtonData multiKeys[] = {
    MultiButtonData{A7, -1, 0, 0, walkerXButtons},
    MultiButtonData{A6, -1, 0, 0, walkerYButtons},
    MultiButtonData{-1, 0, 0, 0, nullptr}
};

void setup() {
    Keyboard.begin();
    initializeButtons(buttons);
    initializeButtons(keys);
    initializeAxes(axes);
    initializeMultiButtons(multiButtons);
    initializeMultiButtons(multiKeys);
    // Serial.begin(115200);
}

JoystickButtonController joystickButtonController{joystick};
KeyboardButtonController keyboardButtonController;

void loop() {
    // Serial.println("loop");
    processButtons(joystickButtonController, buttons);
    processButtons(keyboardButtonController, keys);
    processAxes(joystick, axes);
    processMultiButtons(joystickButtonController, multiButtons);
    processMultiButtons(keyboardButtonController, multiKeys);
    joystick.sendState();
}

