cmake_minimum_required(VERSION 3.19)

project(keyboard LANGUAGES CXX)

# Ensure correct Qt version and modules 
set(CMAKE_PREFIX_PATH "/usr/lib/qt6")
find_package(Qt6 6.4 REQUIRED COMPONENTS Core Widgets Multimedia MultimediaWidgets )

# Standard Qt setup: includes C++ standard, warnings, etc.
qt_standard_project_setup()

# Define the executable and UI/Source files
qt_add_executable(keyboard
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ui_mainwindow.h
    # include keyboard files
    keyboard/widgetKeyBoard.cpp
    keyboard/QKeyPushButton.cpp
    keyboard/widgetKeyBoard.h
    keyboard/QKeyPushButton.h
)

# Link necessary Qt libraries
target_link_libraries(keyboard
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia 
        Qt6::MultimediaWidgets 
)

# Install rules
include(GNUInstallDirs)

install(TARGETS keyboard
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


