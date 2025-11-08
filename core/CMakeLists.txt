# Create the Core static library
add_library(Core_Lib STATIC
        index.cpp
        main_area.cpp
        utils.h
)

# Define the Public Interface (Headers that UI/App will include)
target_include_directories(Core_Lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/.. # Assumes Core headers are directly in Core/ (index.h, main_area.h)
)

# Core shouldn't need to link to Qt Widgets unless it uses QObject features
# If it uses QObject, it needs Qt::Core
# target_link_libraries(Core_Lib PRIVATE Qt${QT_VERSION_MAJOR}::Core)