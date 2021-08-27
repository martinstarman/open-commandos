# SEC File format
Describe map sectors.

| block type | description |
| - | - |
| integer | number of vertices (v1) |
| float float | x and y position of vertex, repeated 'v1' times |
| integer | number of sectors |
| integer integer integer integer integer integer integer integer | number of vertices (v2), TODO(describe remaining numbers) |
| integer | position of vertex from previous section, repeated 'v2' times |
| integer | number of bridges |
| TODO(?) | TODO(?) |
| integer | number of areas |
| TODO(?) | TODO(?) |
| integer | number of connected sectors |
| TODO(?) | TODO(?) |