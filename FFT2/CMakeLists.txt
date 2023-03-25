
set(SOURCES
        main.cpp
        FFT.cpp
        )

find_package(SFML COMPONENTS audio system window graphics CONFIG REQUIRED)

set(TARGET_NAME FFT2)
add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE sfml-system)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-network)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-graphics)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-window)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-audio)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
		COMMENT "Copy resources to target directory"
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/Resources"
		"$<TARGET_FILE_DIR:${TARGET_NAME}>/Resources")
