#ifndef BUTTONPRESSER_HPP
#define BUTTONPRESSER_HPP

#include "Pressable.hpp"

class ButtonPresser {
public:
    ButtonPresser(Joystick_& joystick, Pressable button)
            : joystick(joystick), button(button) {
    }

    void update() {
        if (releaseTime != 0 && millis() >= releaseTime) {
            button.process(joystick, false);
            releaseTime = 0;
        }
    }

    void press() {
        button.process(joystick, true);
        releaseTime = millis() + releaseDelay;
    }

private:
    Joystick_& joystick;
    Pressable button;
    unsigned long releaseTime = 0;

    static constexpr int releaseDelay = 100;
};

#endif // BUTTONPRESSER_HPP
