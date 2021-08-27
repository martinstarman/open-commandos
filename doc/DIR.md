# DIR file format
Archive containing all game data.

| block name | block size (bytes) | description |
| - | - | - |
| Entries | x ||

## Entry format

| block name | block size (bytes) | description|
| - | -| - |
| name | 32 ||
| type | 1 | -1 = end, 0 = file, 1 = dir |
| unknown | 3 ||
| size | 4 ||
| offset | 4 | file/dir start offset |
