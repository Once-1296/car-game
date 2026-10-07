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

# Dev convenience: when run straight out of the build tree (no install
# step), the game looks for assets/ next to its own binary, so keep a copy
# there. This mirrors the <prefix>/bin + <prefix>/share/car-racing layout
# that `cmake --install` produces below, just without a prefix.
add_custom_command(TARGET car-racing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:car-racing>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:car-racing>/data
)

# Real install: `cmake --install build` (add --prefix ~/.local for a
# user-level, no-root install). The binary locates these at runtime
# relative to its own path (see support::initPaths), not the working
# directory, so it can be launched from anywhere after this.
include(GNUInstallDirs)

install(TARGETS car-racing RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY assets/ DESTINATION ${CMAKE_INSTALL_DATADIR}/car-racing/assets)
install(DIRECTORY data/ DESTINATION ${CMAKE_INSTALL_DATADIR}/car-racing/data)

configure_file(
    packaging/car-racing.desktop.in
    ${CMAKE_CURRENT_BINARY_DIR}/car-racing.desktop
    @ONLY
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/car-racing.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)
