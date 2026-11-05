cmake_minimum_required(VERSION 3.22)
project(tripletriad C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find curses
find_package(Curses REQUIRED)

# Main executable
add_executable(tripletriad
    src/main.c
    src/pliki.c
    src/interfejs.c
    src/zasady.c
    src/midi_player.cpp
)

target_include_directories(tripletriad PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(tripletriad PRIVATE ${CURSES_LIBRARIES} m)

# Sound disabled — AudioToolbox no longer needed

target_compile_features(tripletriad PRIVATE cxx_std_20)
