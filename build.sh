g++                          \
  -o build/opencommandos.exe \
  src/main.cpp               \
  src/utils/bmp_file.cpp     \
  src/utils/dir_file.cpp     \
  src/utils/rle_file.cpp     \
  src/utils/utils.cpp        \
  src/utils/wad_file.cpp     \
  -I include                 \
  -L lib                     \
  -lraylib                   \
  -lgdi32                    \
  -lwinmm
