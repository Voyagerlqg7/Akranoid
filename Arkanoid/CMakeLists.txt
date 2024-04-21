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

# Указываем пути к заголовочным файлам и cpp файлам
set(HEADERS
    include/paddle.h
    include/brick.h
    include/ball.h
    include/breakout.h
)
set(SOURCES
    src/main.cpp
    src/paddle.cpp
    src/brick.cpp
    src/ball.cpp
    src/breakout.cpp
)

# Добавляем пути к заголовочным файлам и cpp файлам в проект
qt_add_executable(Arkanoid ${HEADERS} ${SOURCES})

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
