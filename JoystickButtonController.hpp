#ifndef JOYSTICKBUTTONCONTROLLER_HPP
#define JOYSTICKBUTTONCONTROLLER_HPP

#include <Joystick.h>

class JoystickButtonController {
public:
    JoystickButtonController(Joystick_& joystick) : joystick(joystick) {}

    void setButtonValue(int button, bool value) {
        joystick.setButton(button, value);
    }
private:
    Joystick_& joystick;
};


#endif // JOYSTICKBUTTONCONTROLLER_HPP
