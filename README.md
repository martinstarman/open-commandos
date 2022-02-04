# GreenBeret

GreenBeret is project to create a free engine for games Commandos: Behind Enemy Lines and
Commandos: Beyond the Call of Duty.

GreenBeret uses the original game assets. For playing, you need original game. Available for
example on Steam.

## Goals

- keep the code as simple as possible
- run BEL and BtCoD on modern computers
- simplify map creating - map editor
- cooperation
- ...

## Building

- install cmake
- run ```cmake . -Bbuild -DSDL2_PATH=<path-to-sdl2>```
- run ```cmake --build build```

## Running

- build GreenBeret project
- copy WARGAME.DIR file to build directory
- run greenberet.exe
