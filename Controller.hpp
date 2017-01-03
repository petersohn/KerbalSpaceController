#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <Joystick.h>

struct ButtonData {
    int pin;
    int targetButton;
};

inline
void processButtons(Joystick_& joystick, const ButtonData buttons[]) {
    for (const ButtonData* button = buttons; button->pin >= 0; ++button) {
        joystick.setButton(button->targetButton, !digitalRead(button->pin));
    }
}

inline
void initializeButtons(const ButtonData buttons[]) {
    for (const ButtonData* button = buttons; button->pin >= 0; ++button) {
        pinMode(button->pin, INPUT_PULLUP);
    }
}

#endif // CONTROLLER_HPP
