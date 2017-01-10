#ifndef KEYBOARDBUTTONCONTROLLER_HPP
#define KEYBOARDBUTTONCONTROLLER_HPP

#include <Keyboard.h>

class KeyboardButtonController {
public:
    void setButtonValue(int button, bool value) {
        if (value) {
            Keyboard.press(button);
        } else {
            Keyboard.release(button);
        }
    }
};


#endif // KEYBOARDBUTTONCONTROLLER_HPP
