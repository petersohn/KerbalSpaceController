#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <Joystick.h>

struct ButtonData {
    int pin;
    int targetButton;
};

inline
void initializeButtons(const ButtonData buttons[]) {
    for (const ButtonData* button = buttons; button->pin >= 0; ++button) {
        pinMode(button->pin, INPUT_PULLUP);
    }
}

inline
void processButtons(Joystick_& joystick, const ButtonData buttons[]) {
    for (const ButtonData* button = buttons; button->pin >= 0; ++button) {
        joystick.setButton(button->targetButton, !digitalRead(button->pin));
    }
}

struct AxisData {
    int pin;
    void (Joystick_::*function)(int);
};

inline
void initializeAxes(const AxisData axes[]) {
    for (const AxisData* axis = axes; axis->pin >= 0; ++axis) {
        pinMode(axis->pin, INPUT);
    }
}

inline
void processAxes(Joystick_& joystick, const AxisData axes[]) {
    for (const AxisData* axis = axes; axis->pin >= 0; ++axis) {
        (joystick.*(axis->function))(analogRead(axis->pin));
    }
}


#endif // CONTROLLER_HPP
