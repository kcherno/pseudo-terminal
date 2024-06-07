set(SOURCE_FILES
    test-mutable-buffer.cpp)

find_library(BOOSTTEST libboost_unit_test_framework.a)

if (EXISTS ${BOOSTTEST})
    foreach(SOURCE_FILE ${SOURCE_FILES})
	get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

	add_executable(${TARGET_NAME} ${SOURCE_FILE})

	target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

	target_link_libraries(${TARGET_NAME} PUBLIC ${BOOSTTEST})

    endforeach()

else()
    message(WARNING "Boost.Test library not found")

endif()
