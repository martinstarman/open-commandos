# VOL File format
Map file.

| value | description |
| - | - |
| MAPDIMXY integer,integer | map size - width and height |
| POLY string,integer,integer,integer,integer,integer,integer | polygon - name, center x, center y, center z, height, number of vertices, number of tiles |
| POINT integer,integer | vertex - x, y |
| TILE integer,integer,integer,integer,integer,integer,integer,string,string | tile - x, y, width, height, offset x, offset y, brighthness, sprite name (name starts with '-' is invisible), transformation (X = horizontal flip, Y = vertical flip) |
| TODO | TODO |
