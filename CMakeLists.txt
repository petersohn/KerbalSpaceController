project(KerbalSpaceController)
cmake_minimum_required(VERSION 3.6)

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

SET(JOYSTICK_DIR "${CMAKE_CURRENT_LIST_DIR}/ArduinoJoystickLibrary/Joystick/src")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14 -I${JOYSTICK_DIR} -fno-threadsafe-statics" )

generate_arduino_library(Joystick
    SRCS "${JOYSTICK_DIR}/Joystick.cpp" "${JOYSTICK_DIR}/DynamicHID.cpp"
    HDRS "${JOYSTICK_DIR}/Joystick.h" "${JOYSTICK_DIR}/DynamicHID.h"
    BOARD leonardo)

generate_arduino_firmware(board1
    SRCS board1.cpp
    HDRS Controller.hpp "${JOYSTICK_DIR}/Joystick.h"
    LIBS Joystick
    PORT /dev/ttyACM0
    PROGRAMMER avrispmkii
    BOARD leonardo)

generate_arduino_firmware(board2
    SRCS board2.cpp
    HDRS Controller.hpp "${JOYSTICK_DIR}/Joystick.h"
    LIBS Joystick
    PORT /dev/ttyACM1
    PROGRAMMER avrispmkii
    BOARD leonardo)
