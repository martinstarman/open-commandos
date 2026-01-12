# RLE file
256 colors bitmap with compressed transparent pixels.

| block name          | bytes        | description                    |
| ------------------- | ------------ | ------------------------------ |
| header              | 64           |                                |
| pixels              |              |                                |
| line offsets header | 16           |                                |
| line offsets        | `height` * 4 | offset for every line in image |
| palette index       | 4            | index of palette in WAD file   |

## `header` format

| name             | bytes | description |
| ---------------- | ----- | ----------- |
| name             | 32    | file name   |
| number of pixels | 8     |             |
| unknown          | 8     |             |
| height           | 4     |             |
| width            | 4     |             |
| color depth      | 2     |             |
| unknown          | 6     |             |

## `pixel` value format
| type                  | description                                                                                  |
| --------------------- | -------------------------------------------------------------------------------------------- |
| transparent pixel     | starts with `0xFF`, then follows the number of pixels                                        |
| semitransparent pixel | starts with `0xFE`, then follows the number of pixels, then follows pixel indexes in palette |
| opaque pixel          | starts with number of pixels, then follows pixel indexes in palette                          |

## `line offsets header` format

| name   | bytes | description                       |
| ------ | ----- | --------------------------------- |
| size   | 4     |                                   |
| name   | 4     |                                   |
| width  | 4     | equals `width` in `header` block  |
| height | 4     | equals `height` in `header` block |
