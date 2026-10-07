cmake_minimum_required(VERSION 3.16)
project(car-racing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 3 components (capitalized names, namespaced targets)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio Network)

add_executable(car-racing
    src/main.cpp
    src/support.cpp
    src/support.h
)

target_link_libraries(car-racing PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    SFML::Network
)

# The game reads its assets/save data relative to the working directory at
# runtime, so keep them alongside the built binary.
add_custom_command(TARGET car-racing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:car-racing>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:car-racing>/data
)
