#ifndef PRESSABLE_HPP
#define PRESSABLE_HPP

#include <Joystick.h>
#include <Keyboard.h>

class Pressable {
public:
    enum class Type {
        None, Key, Button
    };

    Pressable(Type type, int button) : type(type), button(button) {}

    void process(Joystick_& joystick, bool value) {
        if (button < 0) {
            return;
        }
        switch (type) {
        case Type::Key:
            if (value) {
                Keyboard.press(button);
            } else {
                Keyboard.release(button);
            }
            break;
        case Type::Button:
            joystick.setButton(button, value);
            break;
        default:
            break;
        }
    }

    Type getType() const { return type; }
    explicit operator bool() const { return type != Type::None; }
    bool operator!() const { return type == Type::None; }
private:
    Type type;
    int button;
};

template<Pressable::Type T>
class FixedPressable : public Pressable {
public:
    explicit FixedPressable(int button) : Pressable{T, button} {}
};

class None : public Pressable {
public:
    explicit None() : Pressable{Pressable::Type::None, -1} {}
};

using Key = FixedPressable<Pressable::Type::Key>;
using Button = FixedPressable<Pressable::Type::Button>;

#endif // PRESSABLE_HPP
