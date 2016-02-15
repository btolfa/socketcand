cmake_minimum_required(VERSION 3.3.1 FATAL_ERROR)

project(socketcand C)

find_package(Threads REQUIRED)

set(SRC
    socketcand.c
    statistics.c
    beacon.c
    state_raw.c
    state_isotp.c
    state_control.c
)

add_executable(socketcand ${SRC})
target_include_directories(socketcand PUBLIC
        include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(socketcand Threads::Threads)