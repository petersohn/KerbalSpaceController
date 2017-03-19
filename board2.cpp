#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>
#include <Keyboard.h>

#include "AxisProcessor.hpp"
#include "ButtonProcessor.hpp"
#include "Controller.hpp"
#include "MultiButtonProcessor.hpp"

Joystick_ joystick(0x04, JOYSTICK_TYPE_JOYSTICK,
    16, 0, // button, hat switch
    true, true, true, // x, y, z
    true, true, true, // rx, ry, rz
    false, false, // rudder, throttle
    false, false, false); // accelerator, brake, steering

ButtonProcessor buttons[] = {
    ButtonProcessor{0, Button{0}},
    ButtonProcessor{1, Button{1}},
    ButtonProcessor{2, Button{2}},
    ButtonProcessor{3, Key{KEY_ESC}},
    ButtonProcessor{5, Key{KEY_F9}},
    ButtonProcessor{7, Key{KEY_F5}},
    ButtonProcessor{11, Button{3}},
    ButtonProcessor{13, Button{4}},
    ButtonProcessor{}
};

AxisProcessor axes[] = {
    AxisProcessor{A0, &Joystick_::setZAxis},
    AxisProcessor{A1, &Joystick_::setYAxis},
    AxisProcessor{A2, &Joystick_::setXAxis},
    AxisProcessor{A3, &Joystick_::setRzAxis},
    AxisProcessor{A4, &Joystick_::setRyAxis},
    AxisProcessor{A5, &Joystick_::setRxAxis},
    AxisProcessor{}
};

Pressable walkerXButtons[] = {Key('a'), Button{-1}, Key('d'), None{}};
Pressable walkerYButtons[] = {Key('w'), Button{-1}, Key('s'), None{}};
Pressable walkerTurnButtons[] = {Key('q'), Button{-1}, Key('e'), None{}};
Pressable sasButtons[] = {Button{5}, Button{6}, Button{7}, Button{8},
        Button{9}, Button{10}, Button{11}, Button{12}, Button{13}, Button{14},
        Button{15}, None{}};

MultiButtonProcessor multiButtons[] = {
    MultiButtonProcessor{A7, -1, walkerXButtons},
    MultiButtonProcessor{A6, -1, walkerYButtons},
    MultiButtonProcessor{A10, -1, walkerTurnButtons},
    MultiButtonProcessor{A8, 9, sasButtons},
    MultiButtonProcessor{}
};

void setup() {
    // Serial.begin(115200);
    joystick.begin(false);
    Keyboard.begin();
    Serial.begin(115200);
}

void loop() {
    // Serial.println("loop");
    processElements(joystick, buttons);
    processElements(joystick, axes);
    processElements(joystick, multiButtons);
    joystick.sendState();
}

