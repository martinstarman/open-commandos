# DIR file format
Archive containing all game data as list of entries. 

## `entry` format

| block name | bytes | description                                                                |
| ---------- | ----- | -------------------------------------------------------------------------- |
| `name`     | 32    | `\0` terminated                                                            |
| `type`     | 1     |                                                                            |
| `padding`  | 3     |                                                                            |
| `size`     | 4     | size of the file, `0x0000` for directory, `0xFFFF` for end of directory    |
| `offset`   | 4     | current file/first file in directory offset, `0xFFFF` for end of directory |

## `type` block values
| value | hexadecimal value | description   |
| ----- | ----------------- | ------------- |
| -1    | `0xFF`            | directory end |
| 0     | `0x00`            | file          |
| 1     | `0x01`            | directory     |
