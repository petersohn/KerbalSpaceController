#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <Joystick.h>

struct ButtonData {
    int pin;
    int targetButton;
};

template<typename Buttons>
void processButtons(Joystick& joystick, const Buttons& buttons) {
    for (const ButtonData button : buttons) {
        joystick.setButton(button.targetButton, !digitalRead(button.pin));
    }
}

#endif // CONTROLLER_HPP
