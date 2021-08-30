project(greenberet)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# cmake command ard -DSDL2_PATH=<path>
find_package(SDL2 REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/Window.cpp
    src/Game.cpp
    src/Map.cpp
    src/Vector2.cpp
    src/Polygon.cpp
    src/Sector.cpp
    src/Tile.cpp
    src/DIRFile.cpp
    src/VOLFile.cpp
    src/WADFile.cpp
    src/BMPFile.cpp
    src/RLEFile.cpp
    src/SECFile.cpp
    src/Utils.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    SDL2::SDL2
)
