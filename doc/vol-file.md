# VOL file
TBD

## Format

| keyword                                                                                                    | description                                                                                                  |
| ---------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------ |
| `MAPDIMXY <width> <height>`                                                                                | map dimensions                                                                                               |
| `MAPTABPOLYS`                                                                                              | TBD                                                                                                          |
| `POLY <name>, <center x>, <center y>, <center z>, <height>, <number of vertices>, <number of tiles>`       | polygon                                                                                                      |
| `RADIO <number>`                                                                                           | TBD                                                                                                          |
| `TILE <x>, <y>, <width>, <height>, <offset x>, <offset y>, <brighthness>, <sprite name>, <transformation>` | sprite name starting with '-' is invisible, transformation - X = horizontal flip, Y = vertical flip, L = TBD |
| `EXTRAINFO <number>, <number>, <number>, <number>, <number>, <number>, <number>, <number>`                 | TBD                                                                                                          |
| `POINT <x> <y>`                                                                                            | polygon point relative to polygon center                                                                     |
| `;`                                                                                                        | comment                                                                                                      |
| `POLYRAMPA `                                                                                               | TBD                                                                                                          |
