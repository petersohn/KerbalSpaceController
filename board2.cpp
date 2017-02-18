#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>
#include <Keyboard.h>

#include "Controller.hpp"

Joystick_ joystick(0x04, JOYSTICK_TYPE_JOYSTICK,
    16, 0, // button, hat switch
    true, true, true, // x, y, z
    true, true, true, // rx, ry, rz
    false, false, // rudder, throttle
    false, false, false); // accelerator, brake, steering

ButtonData buttons[] = {
    ButtonData{0, Button{0}},
    ButtonData{1, Button{1}},
    ButtonData{2, Button{2}},
    ButtonData{3, Key{KEY_ESC}},
    ButtonData{5, Key{KEY_F9}},
    ButtonData{7, Key{KEY_F5}},
    ButtonData{11, Button{3}},
    ButtonData{13, Button{4}},
    ButtonData{}
};

AxisData axes[] = {
    AxisData{A0, &Joystick_::setZAxis},
    AxisData{A1, &Joystick_::setYAxis},
    AxisData{A2, &Joystick_::setXAxis},
    AxisData{A3, &Joystick_::setRzAxis},
    AxisData{A4, &Joystick_::setRyAxis},
    AxisData{A5, &Joystick_::setRxAxis},
    AxisData{}
};

Pressable walkerXButtons[] = {Key('a'), Button{-1}, Key('d'), None{}};
Pressable walkerYButtons[] = {Key('w'), Button{-1}, Key('s'), None{}};
Pressable sasButtons[] = {Button{5}, Button{6}, Button{7}, Button{8},
        Button{9}, Button{10}, Button{11}, Button{12}, Button{13}, Button{14},
        Button{15}, None{}};

MultiButtonData multiButtons[] = {
    MultiButtonData{A7, -1, walkerXButtons},
    MultiButtonData{A6, -1, walkerYButtons},
    MultiButtonData{A8, 9, sasButtons},
    MultiButtonData{}
};

void setup() {
    // Serial.begin(115200);
    joystick.begin(false);
    Keyboard.begin();
    Serial.begin(115200);
}

void loop() {
    // Serial.println("loop");
    processButtons(joystick, buttons);
    processAxes(joystick, axes);
    processMultiButtons(joystick, multiButtons);
    joystick.sendState();
}

