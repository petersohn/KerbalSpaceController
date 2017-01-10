#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "LazyChanger.hpp"

#include <Joystick.h>

struct ButtonData {
    int pin;
    int targetButton;
    LazyChanger<bool> changer;


    ButtonData() : pin(-1), targetButton(-1) {}

    ButtonData(int pin, int targetButton) :
            pin(pin), targetButton(targetButton), changer{false} {
        pinMode(pin, INPUT_PULLUP);
    }
};

inline
void processButtons(Joystick_& joystick, ButtonData buttons[]) {
    for (ButtonData* button = buttons; button->pin >= 0; ++button) {
        button->changer.update(!digitalRead(button->pin),
                [&joystick, button](bool value) {
                    joystick.setButton(button->targetButton, value);
                });
    }
}

struct AxisData {
    using AxisMethod = void(Joystick_::*)(int);
    using ExtraAction = void(*)(int);
    int pin;
    AxisMethod function;
    ExtraAction extraAction;
    LazyChanger<int> changer;

    AxisData() : pin(-1), function(nullptr) {}

    AxisData(int pin, AxisMethod function, ExtraAction extraAction = nullptr) :
            pin(pin), function(function), extraAction(extraAction),
            changer{512} {
        pinMode(pin, INPUT);
    }
};

inline
void processAxes(Joystick_& joystick, AxisData axes[]) {
    for (AxisData* axis = axes; axis->pin >= 0; ++axis) {
        axis->changer.update(analogRead(axis->pin),
                [&joystick, axis](int value) {
                    (joystick.*(axis->function))(value);
                    if (axis->extraAction) {
                        (*axis->extraAction)(value);
                    }
                });
    }
}

struct MultiButtonData {
    int pin;
    int guardPin;
    int numButtons;
    int valueRange;
    int* buttons;
    LazyChanger<int> changer;

    MultiButtonData() :
            pin(-1), guardPin(-1), numButtons(0), valueRange(0),
            buttons(nullptr) {}

    MultiButtonData(int pin, int guardPin, int* buttons) :
            pin(pin), guardPin(guardPin), numButtons(0), valueRange(0),
            buttons(buttons), changer{0} {
        pinMode(pin, INPUT);
        if (guardPin >= 0) {
            pinMode(guardPin, INPUT_PULLUP);
        }
        for (const int* button = buttons; *button > -2; ++button) {
            ++numButtons;
        }
        valueRange = 1024 / numButtons;
        if (1024 % numButtons != 0) {
            ++valueRange;
        }
    }
};

inline
void processMultiButtons(Joystick_& joystick, const MultiButtonData buttons[]) {
    for (const MultiButtonData* data = buttons; data->pin >= 0; ++data) {
        if (data->guardPin >= 0 && !digitalRead(data->guardPin)) {
            for (int i = 0; i < data->numButtons; ++i) {
                if (data->buttons[i] >= 0) {
                    joystick.setButton(data->buttons[i], false);
                }
            }
            continue;
        }
        int pinValue = analogRead(data->pin);
        int value = pinValue / data->valueRange;
        for (int i = 0; i < data->numButtons; ++i) {
            if (data->buttons[i] >= 0) {
                joystick.setButton(data->buttons[i], i == value);
            }
        }
    }
}

#endif // CONTROLLER_HPP
