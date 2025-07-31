g++                          \
  -o build/opencommandos.exe \
  main.cpp                   \
  utils/bmp_file.cpp         \
  utils/dir_file.cpp         \
  utils/rle_file.cpp         \
  utils/utils.cpp            \
  utils/wad_file.cpp         \
  -I include                 \
  -I utils                   \
  -L lib                     \
  -l raylib                  \
  -l gdi32                   \
  -l winmm
