project(KerbalSpaceController)
cmake_minimum_required(VERSION 3.6)

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

function(copy_platform PLATFORM_NAME INPUT_BOARD_ID OUTPUT_BOARD_ID OUTPUT_BOARD_NAME)
    set(SOURCE_PATH ${${ARDUINO_PLATFORM}_PLATFORM_PATH})
    set(TARGET_PATH ${CMAKE_CURRENT_BINARY_DIR}/${PLATFORM_NAME})
    file(COPY ${SOURCE_PATH}/bootloaders DESTINATION ${TARGET_PATH})
    file(COPY ${SOURCE_PATH}/cores DESTINATION ${TARGET_PATH})
    file(COPY ${SOURCE_PATH}/variants DESTINATION ${TARGET_PATH})
    file(COPY ${SOURCE_PATH}/programmers.txt DESTINATION ${TARGET_PATH})
    file(READ ${SOURCE_PATH}/boards.txt BOARDS_LIST)
    execute_process(COMMAND sed -n -e "s/^${INPUT_BOARD_ID}\\./${OUTPUT_BOARD_ID}./p" ${SOURCE_PATH}/boards.txt OUTPUT_FILE ${TARGET_PATH}/boards.txt)
    execute_process(COMMAND sed -i -e "s/^${OUTPUT_BOARD_ID}\\.name=.*/${OUTPUT_BOARD_ID}.name=${OUTPUT_BOARD_NAME}/" ${TARGET_PATH}/boards.txt)
    register_hardware_platform(${TARGET_PATH})
endfunction()

set(JOYSTICK_DIR "${CMAKE_CURRENT_LIST_DIR}/ArduinoJoystickLibrary/Joystick/src")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14 -I${JOYSTICK_DIR} -fno-threadsafe-statics")

copy_platform(avr1 leonardo ksc1 "Kerbal Space Controller 1")
copy_platform(avr2 leonardo ksc2 "Kerbal Space Controller 2")

# print_board_list()

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
    BOARD ksc1)

generate_arduino_firmware(board2
    SRCS board2.cpp
    HDRS Controller.hpp "${JOYSTICK_DIR}/Joystick.h"
    LIBS Joystick
    PORT /dev/ttyACM1
    PROGRAMMER avrispmkii
    BOARD ksc2)
