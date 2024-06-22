set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/terminal/terminal_interface.cpp
    ${PROJECT_SOURCE_DIR}/terminal/screen_interface.cpp
    ${PROJECT_SOURCE_DIR}/ansi/keyboard_keys.cpp)

set(TARGET_NAME_LIBRARY terminal)

add_library(${TARGET_NAME_LIBRARY} STATIC ${SOURCE_FILES})

target_include_directories(${TARGET_NAME_LIBRARY} PUBLIC ${PROJECT_INCLUDE_DIR})
