#ifndef MULTIBUTTONPROCESSOR_HPP
#define MULTIBUTTONPROCESSOR_HPP

#include "LazyChanger.hpp"
#include "Pressable.hpp"

#include <Joystick.h>

struct MultiButtonProcessor {
public:
    MultiButtonProcessor() :
            pin(-1), guardPin(-1), numButtons(0), valueRange(0),
            buttons(nullptr) {}

    MultiButtonProcessor(int pin, int guardPin, Pressable* buttons) :
            pin(pin), guardPin(guardPin), numButtons(0), valueRange(0),
            buttons(buttons), changer{0} {
        pinMode(pin, INPUT);
        if (guardPin >= 0) {
            pinMode(guardPin, INPUT_PULLUP);
        }
        for (const Pressable* button = buttons; *button; ++button) {
            ++numButtons;
        }
        valueRange = 1024 / numButtons;
        if (1024 % numButtons != 0) {
            ++valueRange;
        }
    }

    bool isValid() const { return pin >= 0; }

    void process(Joystick_& joystick) {
        int value = -1;
        if (guardPin < 0 || digitalRead(guardPin)) {
            int pinValue = analogRead(pin);
            value = pinValue / valueRange;
        }
        for (int i = 0; i < numButtons; ++i) {
            buttons[i].process(joystick, i == value);
        }
    }

private:
    int pin;
    int guardPin;
    int numButtons;
    int valueRange;
    Pressable* buttons;
    LazyChanger<int> changer;
};

#endif // MULTIBUTTONPROCESSOR_HPP
