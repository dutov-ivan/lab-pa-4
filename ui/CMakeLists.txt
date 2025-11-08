# UI/CMakeLists.txt

# 1. Use GLOB to find all .ui files in the 'forms' directory.
file(GLOB UI_FILES "forms/*.ui")

# --- Create the UI static library ---
add_library(UI_Lib STATIC
        mainwindow.cpp
        IndexRecordModel.h
        MainRecordModel.h
        dialogs/AddRecordDialog.cpp
        dialogs/AddRecordDialog.h
        # Add mainwindow.h and other headers that need MOC here:
        mainwindow.h
        dialogs/AddRecordDialog.h
        dialogs/EditRecordDialog.cpp
        dialogs/EditRecordDialog.h
        dialogs/GenerateRecordsDialog.cpp
        dialogs/GenerateRecordsDialog.h
        dialogs/SearchRecordsDialog.cpp
        dialogs/SearchRecordsDialog.h
        dialogs/DeleteRecordDialog.cpp
        dialogs/DeleteRecordDialog.h
)

# --- Add Generated and Source Files to the Target ---
target_sources(UI_Lib PRIVATE
        # Include all generated ui_*.h headers (essential for the build)
        ${UI_HEADERS}

        # This line is no longer necessary since UI_HEADERS includes all of them:
        # forms/mainwindow.ui
        # forms/AddRecordDialog.ui
)

# --- Rest of your CMakeLists.txt remains the same ---
target_include_directories(UI_Lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(UI_Lib PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Core_Lib
)