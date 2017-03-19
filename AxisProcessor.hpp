#ifndef AXISPROCESSOR_HPP
#define AXISPROCESSOR_HPP

#include "LazyChanger.hpp"
#include "Pressable.hpp"

#include <Joystick.h>

struct AxisProcessor {
public:
    using AxisMethod = void(Joystick_::*)(int);
    using ExtraAction = void(*)(int);

    AxisProcessor() : pin(-1), function(nullptr) {}

    AxisProcessor(int pin, AxisMethod function, ExtraAction extraAction = nullptr) :
            pin(pin), function(function), extraAction(extraAction),
            changer{512} {
        pinMode(pin, INPUT);
    }

    bool isValid() const { return pin >= 0; }

    void process(Joystick_& joystick) {
        changer.update(analogRead(pin),
                [&joystick, this](int value) {
                    (joystick.*(function))(value);
                    if (extraAction) {
                        (*extraAction)(value);
                    }
                });
    }

private:
    int pin;
    AxisMethod function;
    ExtraAction extraAction;
    LazyChanger<int> changer;
};

#endif // AXISPROCESSOR_HPP
