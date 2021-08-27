# RLE File Format
256 colors bitmap with transparent pixels. Transparent pixels are compressed.

| block name | size (bytes) | description |
| - | - | - |
| header | 64 ||
| pixels | number of pixels in header block | transparent pixels - starts with 0xFF, follows with number of pixels; semi transparent pixels - starts with 0xFE, follows with number of pixels and pixels values; opaque pixels - start with number of pixels, follows pixels values |
| line offsets | 16 ||
| palette id | 4 | index of palette in WAD file  |

## Block "header" format

| name | size (bytes) | description |
| - | - | - |
| name | 32 ||
| number of pixels | 8 ||
| unknown | 8 ||
| height | 4 ||
| width | 4 ||
| color depth | 2 ||
| unknown | 6 ||

## Block "line offsets" format

| name | size (bytes) | description |
| - | - | - |
| size | 4 | number of entries. equals h * 4 bytes |
| name | 4 ||
| width | 4 ||
| height | 4 ||
