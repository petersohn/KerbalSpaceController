#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Joystick.h>
#include <Keyboard.h>

#include "AxisProcessor.hpp"
#include "Controller.hpp"
#include "MultiButtonProcessor.hpp"
#include "MultiplexerProcessor.hpp"

Joystick_ joystick(0x04, JOYSTICK_TYPE_JOYSTICK,
    16, 0, // button, hat switch
    true, true, true, // x, y, z
    true, true, true, // rx, ry, rz
    false, false, // rudder, throttle
    false, false, false); // accelerator, brake, steering

int multiplexerAddressPins[] = {0, 1, 2, 3, 5, 7};

Multiplexer multiplexer{12, multiplexerAddressPins};

MultiplexerProcessor multiplexerButtons[] = {
    MultiplexerProcessor{multiplexer, 000, Key{KEY_ESC}},
    MultiplexerProcessor{multiplexer, 001, Key{KEY_F9}},
    MultiplexerProcessor{multiplexer, 002, Key{KEY_F5}},
    MultiplexerProcessor{multiplexer, 003, Button{0}},
    MultiplexerProcessor{multiplexer, 004, Button{1}},
    MultiplexerProcessor{multiplexer, 005, Button{2}},
    MultiplexerProcessor{multiplexer, 006, Button{3}},
    MultiplexerProcessor{multiplexer, 007, Key{'1'}},
    MultiplexerProcessor{multiplexer, 010, Key{'2'}},
    MultiplexerProcessor{multiplexer, 011, Key{'3'}},
    MultiplexerProcessor{multiplexer, 012, Key{'4'}},
    MultiplexerProcessor{multiplexer, 013, Key{'5'}},
    MultiplexerProcessor{multiplexer, 014, Key{'6'}},
    MultiplexerProcessor{multiplexer, 015, Key{'7'}},
    MultiplexerProcessor{multiplexer, 016, Key{'8'}},
    MultiplexerProcessor{multiplexer, 017, Key{'9'}},
    MultiplexerProcessor{multiplexer, 020, Key{'0'}},
    MultiplexerProcessor{multiplexer, 021, Key{KEY_LEFT_SHIFT}},
    MultiplexerProcessor{multiplexer, 022, Key{KEY_RIGHT_SHIFT}},
    MultiplexerProcessor{}
};

AxisProcessor axes[] = {
    AxisProcessor{A0, &Joystick_::setZAxis},
    AxisProcessor{A1, &Joystick_::setYAxis},
    AxisProcessor{A2, &Joystick_::setXAxis},
    AxisProcessor{A3, &Joystick_::setRzAxis},
    AxisProcessor{A4, &Joystick_::setRyAxis},
    AxisProcessor{A5, &Joystick_::setRxAxis},
    AxisProcessor{}
};

Pressable walkerXButtons[] = {Key('a'), Button{-1}, Key('d'), None{}};
Pressable walkerYButtons[] = {Key('w'), Button{-1}, Key('s'), None{}};
Pressable walkerTurnButtons[] = {Key('q'), Button{-1}, Key('e'), None{}};
Pressable sasButtons[] = {Button{5}, Button{6}, Button{7}, Button{8},
        Button{9}, Button{10}, Button{11}, Button{12}, Button{13}, Button{14},
        Button{15}, None{}};

MultiButtonProcessor multiButtons[] = {
    MultiButtonProcessor{A7, -1, walkerXButtons},
    MultiButtonProcessor{A6, -1, walkerYButtons},
    MultiButtonProcessor{A10, -1, walkerTurnButtons},
    MultiButtonProcessor{A8, 9, sasButtons},
    MultiButtonProcessor{}
};

void setup() {
    // Serial.begin(115200);
    joystick.begin(false);
    Keyboard.begin();
    Serial.begin(115200);
}

void loop() {
    // Serial.println("loop");
    processElements(joystick, multiplexerButtons);
    processElements(joystick, axes);
    processElements(joystick, multiButtons);
    joystick.sendState();
}

