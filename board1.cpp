#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "AxisProcessor.hpp"
#include "ButtonPresser.hpp"
#include "ButtonProcessor.hpp"
#include "Controller.hpp"
#include "MultiButtonProcessor.hpp"

#include <Joystick.h>

Joystick_ joystick(0x03, JOYSTICK_TYPE_JOYSTICK,
    15, 0, // button, hat switch
    true, true, false, // x, y, z
    false, false, false, // rx, ry, rz
    false, true, // rudder, throttle
    true, false, true); // accelerator, brake, steering

ButtonProcessor buttons[] = {
    ButtonProcessor{0, Button{0}},
    ButtonProcessor{1, Button{1}},
    ButtonProcessor{2, Button{2}},
    ButtonProcessor{3, Button{3}},
    ButtonProcessor{4, Button{4}},
    ButtonProcessor{5, Button{5}},
    ButtonProcessor{6, Button{6}},
    ButtonProcessor{7, Button{7}},
    ButtonProcessor{9, Button{8}},
    ButtonProcessor{10, Button{9}},
    ButtonProcessor{11, Button{10}},
    ButtonProcessor{12, Button{12}},
    ButtonProcessor{13, Button{11}},
    ButtonProcessor{}
};

ButtonPresser throttleKiller{joystick, Button{12}};

void postProcessThrottle(int value) {
    if (value == 0) {
        throttleKiller.press();
    }
}

AxisProcessor axes[] = {
    AxisProcessor{A1, &Joystick_::setYAxis},
    AxisProcessor{A2, &Joystick_::setXAxis},
    AxisProcessor{A3, &Joystick_::setAccelerator},
    AxisProcessor{A4, &Joystick_::setSteering},
    AxisProcessor{A5, &Joystick_::setThrottle, &postProcessThrottle},
    AxisProcessor{}
};

Pressable zoomButtons[] = {Button{13}, Button{-1}, Button{14}, None{}};

MultiButtonProcessor multiButtons[] = {
    MultiButtonProcessor{A0, -1, zoomButtons},
    MultiButtonProcessor{}
};

void setup() {
    joystick.begin(false);
    Serial.begin(115200);
}

void loop() {
    processElements(joystick, buttons);
    processElements(joystick, axes);
    processElements(joystick, multiButtons);
    throttleKiller.update();
    joystick.sendState();
}
