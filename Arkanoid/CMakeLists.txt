cmake_minimum_required(VERSION 3.24.3)
project(Arkanoid LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    src/main.cpp
    src/Arkanoid.h
    src/Arkanoid.cpp
    src/Item.h 
)

qt_add_executable(Arkanoid ${PROJECT_SOURCES})

set_target_properties(Arkanoid
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(Arkanoid
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
