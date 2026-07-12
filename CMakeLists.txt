cmake_minimum_required(VERSION 3.16)

#defines name and version of the project, as well as the programming language used
project(
    GameBoy-Emulator
    VERSION 1.0
    LANGUAGES CXX
)

#sets the C++ standard to C++20, and ensures that it is required and that no compiler-specific extensions are used
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



#finds the SDL2 library and makes it available for use in the project. If SDL2 is not found, an error will be raised
find_package(SDL2 REQUIRED)

# =========================
# Core
# =========================

add_library(
    Core
    src/core/cpu/Cpu.cpp
    src/core/bus/Bus.cpp
    src/core/cartridge/Cartridge.cpp
    src/core/memory/WRam.cpp
    src/core/memory/HRam.cpp
    src/core/ppu/Ppu.cpp
    src/core/timer/Timer.cpp
    
    src/core/joypad/Joypad.cpp
)

target_include_directories(
    Core
    PUBLIC
    src/core/cpu
    src/core/bus
    src/core/cartridge
    src/core/memory
    src/core/ppu
    src/core/timer
    src/core/dma
    src/core/serial
    src/core/joypad

)



# =========================
# Platform:SDL
# =========================

add_library(
    PlatformSDL
    src/frontend/sdl2/PlatformSDL.cpp
)

target_include_directories(
    PlatformSDL
    PUBLIC
    src/frontend/sdl2
)

target_link_libraries(
    PlatformSDL
    PRIVATE
    SDL2::SDL2
)

# =========================
# Executable
# =========================

add_executable(
    GB
    src/main.cpp
)

target_link_libraries(
    GB
    PRIVATE
    Core
    PlatformSDL
)

target_compile_options(
    GB
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
