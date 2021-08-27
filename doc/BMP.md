# BMP file format
256 colors bitmap without transparent pixels.

| block name | block size (bytes) | description |
| - | - | - |
| header | 64 ||
| pixels | number of pixels in header block | each value is index reffering to palette and is exactly 1 pixel in the final image |
| palette id | 4 | index of palette in WAD file |

## Block "header" format
  
| block name | block size (bytes) | description |
| - | - | - |
| name | 32 | file name |
| number of pixels | 8 | = h * (w + 2) + 1, last 2 bytes of every line are same as first bytes, last bytes equals 3rd bytes in file |
| unknown | 8 ||
| height | 4 ||
| width | 4 ||
| color depth | 2 ||
| unknown | 6 ||
