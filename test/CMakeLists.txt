set(SOURCE_FILES
    cursor_interface_test.cpp
    screen_interface_test.cpp
    test-mutable-buffer.cpp)

find_library(BOOSTTEST libboost_unit_test_framework.a)

set(LIST_LIBRARIES
    ${BOOSTTEST}
    terminal)

if (EXISTS ${BOOSTTEST})
    foreach(SOURCE_FILE ${SOURCE_FILES})
	get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

	add_executable(${TARGET_NAME} ${SOURCE_FILE})

	target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})

	target_link_libraries(${TARGET_NAME} PRIVATE ${LIST_LIBRARIES})

    endforeach()

else()
    message(WARNING "Boost.Test library not found")

endif()
