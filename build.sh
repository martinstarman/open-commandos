g++                          \
  -o build/opencommandos.exe \
  main.cpp                   \
  utils/utils.cpp            \
  utils/dir_file.cpp         \
  -I include                 \
  -I utils                   \
  -L lib                     \
  -l raylib                  \
  -l gdi32                   \
  -l winmm
