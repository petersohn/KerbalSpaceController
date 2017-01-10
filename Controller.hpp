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

template<typename ButtonController>
void processButtons(ButtonController& controller, const ButtonData buttons[]) {
    for (const ButtonData* button = buttons; button->pin >= 0; ++button) {
        controller.setButtonValue(
                button->targetButton, !digitalRead(button->pin));
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

struct MultiButtonData {
    int pin;
    int guardPin;
    int numButtons;
    int valueRange;
    int* buttons;
};

inline
void initializeMultiButtons(MultiButtonData buttons[]) {
    for (MultiButtonData* data = buttons; data->pin >= 0; ++data) {
        pinMode(data->pin, INPUT);
        if (data->guardPin >= 0) {
            pinMode(data->guardPin, INPUT_PULLUP);
        }
        data->numButtons = 0;
        for (const int* button = data->buttons; *button > -2; ++button) {
            ++data->numButtons;
        }
        data->valueRange = 1024 / data->numButtons;
        if (1024 % data->numButtons != 0) {
            ++data->valueRange;
        }
    }
}

template<typename ButtonController>
void processMultiButtons(ButtonController& controller,
        const MultiButtonData buttons[]) {
    for (const MultiButtonData* data = buttons; data->pin >= 0; ++data) {
        if (data->guardPin >= 0 && !digitalRead(data->guardPin)) {
            for (int i = 0; i < data->numButtons; ++i) {
                if (data->buttons[i] >= 0) {
                    controller.setButtonValue(data->buttons[i], false);
                }
            }
            continue;
        }
        int pinValue = analogRead(data->pin);
        int value = pinValue / data->valueRange;
        // Serial.print("Pin=");
        // Serial.print(data->pin);
        // Serial.print(" pinValue=");
        // Serial.println(pinValue);
        // Serial.print(" numButtons=");
        // Serial.print(data->numButtons);
        // Serial.print(" valueRange=");
        // Serial.print(data->valueRange);
        // Serial.print(" value=");
        // Serial.print(value);
        // Serial.print(" button=");
        // Serial.println(data->buttons[value]);
        for (int i = 0; i < data->numButtons; ++i) {
            if (data->buttons[i] >= 0) {
                controller.setButtonValue(data->buttons[i], i == value);
            }
        }
    }
}

#endif // CONTROLLER_HPP
