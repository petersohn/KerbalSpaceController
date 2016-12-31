#include <Joystick.h>

Joystick_ joystick(0x03, JOYSTICK_TYPE_JOYSTICK,
    1, 0, // button, hat switch
    false, false, false, // x, y, z
    false, false, false, // rx, ry, rz
    false, false, // rudder, throttle
    false, false, false); // accelerator, brake, steering

void setup() {
    Serial.begin(9600);
    pinMode(0, INPUT_PULLUP);
}

void loop() {
    joystick.setButton(0, !digitalRead(0));
    joystick.sendState();
}
