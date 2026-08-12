cmake_minimum_required(VERSION 4.3)

set (CMAKE_CXX_STANDARD 17)

project(open-commandos)

add_executable(open-commandos)

target_sources(open-commandos
  PRIVATE
  src/area.cpp
  src/bmp_file.cpp
  src/dir_file.cpp
  src/main.cpp
  src/mis_file.cpp
  src/node.cpp
  src/polygon.cpp
  src/rle_file.cpp
  src/sec_file.cpp
  src/sector.cpp
  src/text_file.cpp
  src/tile.cpp
  src/utils.cpp
  src/vol_file.cpp
  src/wad_file.cpp
)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(open-commandos PRIVATE raylib)

find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
target_include_directories(open-commandos PRIVATE ${RAYGUI_INCLUDE_DIRS})
