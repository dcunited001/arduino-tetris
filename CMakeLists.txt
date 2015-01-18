cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME arduino_tetris)

project(${PROJECT_NAME} C CXX)
set(${PROJECT_NAME}_BOARD uno)
set(${PROJECT_NAME}_SRCS main.cpp)
set(${PROJECT_NAME}_PORT /dev/tty.usbmodem1451)

#link_directories(${ARDUINO_SDK}/libraries)

generate_arduino_firmware(${PROJECT_NAME})