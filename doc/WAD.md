# WAD file format
Archive which contains BMP or RLE image files.

| block name | block size (bytes) | description |
| - | - | - |
| header | 400 ||
| number of palettes | 4 ||
| palettes | 525 ||
| number of images | 4 ||
| images | x ||

## Palette format

| block name | block size (bytes) | description |
| - | - | - |
| pallete | 512 | 256 2-byte colors in format RGB565 (G2G1G0B4B3B2B1B0 R4R3R2R1R0G5G4G3) |
| unknown | 13 ||
