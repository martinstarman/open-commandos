# BMP file
256 colors bitmap without transparent pixels.

| block name    | bytes | description                                                                        |
| ------------- | ----- | ---------------------------------------------------------------------------------- |
| header        | 64    |                                                                                    |
| pixels        |       | each value is index reffering to palette and is exactly 1 pixel in the final image |
| palette index | 4     | index of palette in WAD file                                                       |

## `header` format
  
| block name   | bytes | description                                                                                                       |
| ------------ | ----- | ----------------------------------------------------------------------------------------------------------------- |
| name         | 32    | file name                                                                                                         |
| pixels count | 8     | = height * (width + 2) + 1, last 2 bytes of line equals first 2 bytes of line, last byte equals 3rd byte in image |
| unknown      | 8     |                                                                                                                   |
| height       | 4     |                                                                                                                   |
| width        | 4     |                                                                                                                   |
| color depth  | 2     |                                                                                                                   |
| unknown      | 6     |                                                                                                                   |
