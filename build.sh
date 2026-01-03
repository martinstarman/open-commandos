g++                          \
  -o build/opencommandos.exe \
  src/main.cpp               \
  src/utils.cpp              \
  src/file/bmp-file.cpp      \
  src/file/dir-file.cpp      \
  src/file/rle-file.cpp      \
  src/file/wad-file.cpp      \
  -I include                 \
  -L lib                     \
  -lraylib                   \
  -lgdi32                    \
  -lwinmm
