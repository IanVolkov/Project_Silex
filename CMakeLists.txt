cmake_minimum_required(VERSION 3.10)
project(ParticleSimulation VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native -flto")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")

# Find SDL2 using pkg-config (works better on Arch Linux)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# Add executable
add_executable(particle_simulation main.cpp)

# Include directories
target_include_directories(particle_simulation PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Link directories
target_link_directories(particle_simulation PRIVATE
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_TTF_LIBRARY_DIRS}
)

# Link libraries
target_link_libraries(particle_simulation 
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

# Compile options
target_compile_options(particle_simulation PRIVATE
    ${SDL2_CFLAGS_OTHER}
    ${SDL2_TTF_CFLAGS_OTHER}
)

# Installation
install(TARGETS particle_simulation DESTINATION bin)
install(FILES Parameters.txt DESTINATION share/particle_simulation)
