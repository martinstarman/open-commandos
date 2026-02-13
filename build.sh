g++                              \
  -o build/opencommandos.exe     \
  src/main.cpp                   \
  src/polygon.cpp                \
  src/tile.cpp                   \
  src/utils.cpp                  \
  src/file/bmp-file.cpp          \
  src/file/dir-file.cpp          \
  src/file/mis-file.cpp          \
  src/file/node.cpp              \
  src/file/rle-file.cpp          \
  src/file/text-file.cpp         \
  src/file/vol-file.cpp          \
  src/file/wad-file.cpp          \
  -I include                     \
  -L lib                         \
  -lraylib                       \
  -lgdi32                        \
  -lwinmm
