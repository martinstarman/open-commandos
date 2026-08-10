cmake_minimum_required(VERSION 4.3)

set (CMAKE_CXX_STANDARD 17)

project(open-commandos)

add_executable(open-commandos)

target_sources(open-commandos
  PRIVATE
  src/main.cpp
  src/polygon.cpp
  src/tile.cpp
  src/utils.cpp
  src/file/bmp-file.cpp
  src/file/dir-file.cpp
  src/file/mis-file.cpp
  src/file/node.cpp
  src/file/rle-file.cpp
  src/file/text-file.cpp
  src/file/vol-file.cpp
  src/file/wad-file.cpp
)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(open-commandos PRIVATE raylib)

find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
target_include_directories(open-commandos PRIVATE ${RAYGUI_INCLUDE_DIRS})
