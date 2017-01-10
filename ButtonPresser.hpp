#ifndef BUTTONPRESSER_HPP
#define BUTTONPRESSER_HPP

#include <Joystick.h>

class ButtonPresser {
public:
    ButtonPresser(Joystick_& joystick, int button)
            : joystick(joystick), button(button) {
    }

    void update() {
        if (releaseTime != 0 && millis() >= releaseTime) {
            joystick.releaseButton(button);
            releaseTime = 0;
        }
    }

    void press() {
        joystick.pressButton(button);
        releaseTime = millis() + releaseDelay;
    }

private:
    Joystick_& joystick;
    int button;
    unsigned long releaseTime = 0;

    static constexpr int releaseDelay = 100;
};

#endif // BUTTONPRESSER_HPP
