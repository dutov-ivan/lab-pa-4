# ./CMakeLists.txt

cmake_minimum_required(VERSION 3.16)
project(lab4_pa_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect if we need Qt6 or Qt5
if (NOT QT_VERSION_MAJOR)
    find_package(Qt NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
endif ()
if (NOT QT_VERSION_MAJOR)
    set(QT_VERSION_MAJOR 6) # Assume Qt6 if detection fails (modern default)
endif ()

# Global Qt Tools (MOC, UIC, RCC)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find Qt modules once at the top
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# -----------------------------------------------------------
# Add Modular Subdirectories
# -----------------------------------------------------------
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(app) # This directory will hold main.cpp

# --- Installation and Properties (kept from original) ---

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
set_target_properties(lab4_pa_qt PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS lab4_pa_qt
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)