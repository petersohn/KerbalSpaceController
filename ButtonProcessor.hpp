#ifndef BUTTONPROCESSOR_HPP
#define BUTTONPROCESSOR_HPP

#include "LazyChanger.hpp"
#include "Pressable.hpp"

#include <Joystick.h>

class ButtonProcessor {
public:
    ButtonProcessor() : pin(-1), targetButton(None{}) {}

    ButtonProcessor(int pin, Pressable targetButton) :
            pin(pin), targetButton(targetButton), changer{false} {
        pinMode(pin, INPUT_PULLUP);
    }

    bool isValid() const { return pin >= 0; }

    void process(Joystick_& joystick) {
        changer.update(!digitalRead(pin),
                [&joystick, this](bool value) {
                    targetButton.process(joystick, value);
                });
    }

private:
    int pin;
    Pressable targetButton;
    LazyChanger<bool> changer;
};


#endif // BUTTONPROCESSOR_HPP
