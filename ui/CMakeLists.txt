# UI/CMakeLists.txt

# Create the UI static library
add_library(UI_Lib STATIC
        mainwindow.cpp
        IndexRecordModel.h
        MainRecordModel.h
)

# Define the Public Interface (Headers that App will include)
target_include_directories(UI_Lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} # Assumes UI headers are directly in UI/ (mainwindow.h)
)

# Link to necessary Qt modules (Widgets is crucial for UI)
target_link_libraries(UI_Lib PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)

# Link to the Core library
target_link_libraries(UI_Lib PRIVATE Core_Lib)

# Handle .ui files (assuming they are in UI/forms/)
target_sources(UI_Lib PRIVATE
        forms/mainwindow.ui
        mainwindow.h # Add the header for MOC to run on
)