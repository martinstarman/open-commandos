# WAD file
Archive containing BMP and RLE image files.

## Format
| block name                          | bytes | description                            |
| ----------------------------------- | ----- | -------------------------------------- |
| header                              | 400   |                                        |
| number of palettes used in wad file | 4     |                                        |
| palettes                            | 525   |                                        |
| number of images                    | 4     |                                        |
| images                              |       | See BMP/RLE doc for more informations. |

## `header` block format
Unknown.

## `palette` block format

| block name | bytes | description                                                                |
| ---------- | ----- | -------------------------------------------------------------------------- |
| pallete    | 512   | 256 2-byte colors in format `RGB565` (`G2G1G0B4B3B2B1B0 R4R3R2R1R0G5G4G3`) |
| unknown    | 13    |                                                                            |

## Sources
- https://retrogamesvault.com/commandosmod/downloads/CommandosFileTypes.pdf
