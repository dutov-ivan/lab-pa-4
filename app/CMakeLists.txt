# App/CMakeLists.txt

# Define the final executable
if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab4_pa_qt
            MANUAL_FINALIZATION
            main.cpp
    )
else ()
    if (ANDROID)
        add_library(lab4_pa_qt SHARED main.cpp)
    else ()
        add_executable(lab4_pa_qt main.cpp)
    endif ()
endif ()

# Link the executable to the UI and Core libraries
target_link_libraries(lab4_pa_qt PRIVATE
        UI_Lib
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab4_pa_qt)
endif ()