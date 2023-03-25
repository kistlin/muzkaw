
set(SOURCES
        main.cpp
        Particle.cpp
        Slider.cpp
        Utility.cpp
        )

find_package(SFML COMPONENTS audio system window graphics CONFIG REQUIRED)

set(TARGET_NAME ParticlePursuers)
add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE sfml-system)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-network)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-graphics)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-window)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-audio)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMENT "Copy font to target directory"
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/consola.ttf"
        "$<TARGET_FILE_DIR:${TARGET_NAME}>")
