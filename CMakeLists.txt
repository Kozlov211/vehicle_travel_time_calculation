cmake_minimum_required(VERSION 3.11)

project(vehicle_travel_time_calculation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR src/)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

set(MY_CLOCK ${SOURCE_DIR}my_clock.h ${SOURCE_DIR}my_clock.cpp)
set(DEVICE_DATA ${SOURCE_DIR}device_data.h ${SOURCE_DIR}device_data.cpp)
set(PARSE_DATA ${SOURCE_DIR}parse_data.h ${SOURCE_DIR}parse_data.cpp)
set(RESPONSE ${SOURCE_DIR}response.h ${SOURCE_DIR}response.cpp)
set(TEST ${SOURCE_DIR}test_framework.h ${SOURCE_DIR}tests.cpp)
set(MAIN ${SOURCE_DIR}main.cpp)

add_executable(vehicle_travel_time_calculation ${MAIN} ${MY_CLOCK} ${DEVICE_DATA} ${RESPONSE} ${PARSE_DATA} ${TEST})

