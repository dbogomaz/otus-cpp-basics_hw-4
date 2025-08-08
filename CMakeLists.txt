# cmake_minimum_required(VERSION 3.7.2)
cmake_minimum_required(VERSION 3.7.2...3.10)
project(physics)

set(CMAKE_CXX_STANDARD 17)

# Пытаемся найти предустановленный SFML
# find_package(SFML COMPONENTS graphics)
# Явное указание путей для SFML
set(SFML_DIR "/usr/local/opt/sfml/lib/cmake/SFML") 
set(SFML_INCLUDE_DIR "/usr/local/Cellar/sfml/3.0.1/include")
set(SFML_LIBRARY_DIR "/usr/local/Cellar/sfml/3.0.1/lib")
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

if(APPLE)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(COCOA_LIBRARY Cocoa)
endif()

# К сожалению, вплоть до C++20 https://en.cppreference.com/w/cpp/numeric/constants
# нет удобного кроссплатформенного способа получить число pi.
# define ниже нужен для включения M_PI
if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

add_executable(physics
        main.cpp 
        World.cpp 
        Ball.cpp 
        Physics.cpp 
        Color.cpp 
        Painter.cpp
        black_box/Application.cpp 
        black_box/View.cpp 
        black_box/PainterImpl.cpp
        )

target_link_libraries(physics PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
    )

if(APPLE)
    target_link_libraries(physics PRIVATE 
        ${OPENGL_LIBRARY} 
        ${COCOA_LIBRARY}
    )
endif()

target_compile_options(physics PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )
