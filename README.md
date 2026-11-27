*This project has been created as part of the 42 curriculum by admoufle.*

# miniRT

## Description

miniRT is a small ray tracer written in C using MiniLibX. It reads a scene
description file (`.rt`), builds the scene in memory, and renders it in a
window by casting one ray per pixel.

The renderer handles the three mandatory objects — plane, sphere and a closed
cylinder — together with ambient lighting, diffuse lighting and hard shadows
cast by coloured spot lights. Every scene file is fully validated before any
rendering starts: an unknown identifier, a malformed vector, an out of range
colour, a duplicate camera or a missing mandatory element stops the program
with an explicit error message.

Beyond the mandatory part, the project adds specular highlights (Phong model),
multiple spot lights of different colours, a checkerboard pattern on planes,
spheres and cylinders, an adaptive anti-aliasing pass and a progressive display:
the image is drawn across the whole window from the first rendering pass, in an
interleaved order, so the scene is recognisable within the first second instead
of staying black until the end. Rendering happens inside the MiniLibX event
loop, one line at a time, which keeps the window responsive and lets `ESC`
interrupt a running render cleanly.

## Instructions

### Build

```
make            # mandatory binary: ./miniRT
make bonus      # bonus binary:     ./miniRT_bonus
make clean      # remove object files
make fclean     # remove object files and both binaries
make re         # fclean then all
```

The MiniLibX sources are shipped in `minilibx-linux/` and compiled by the
Makefile; X11 development headers (`libx11-dev`, `libxext-dev`, `zlib1g-dev`)
must be installed on the system.

### Run

```
./miniRT scenes/valid/scene.rt
./miniRT_bonus scenes/bonus/presentation.rt
```

`ESC` or the window's close button quits the program.

### Scene format

One element per line, fields separated by any number of spaces or tabs, elements
in any order. Identifiers written with a capital letter may appear only once.

```
A  0.2 255,255,255                      ambient light    ratio, colour
C  -50,0,20 0,0,1 70                   camera           position, direction, fov
L  -40,0,30 0.7 255,255,255            spot light       position, ratio, colour
sp 0,0,20 20 255,0,0                   sphere           centre, diameter, colour
pl 0,0,0 0,1,0 255,0,225               plane            point, normal, colour
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255  cylinder         centre, axis, diameter, height, colour
```

The bonus binary accepts optional values at the end of an `sp`, `pl`, `cy` or `co`
line, **in this order**: the specular intensity (in `[0,1]`), then the specular
exponent (in `[1,1000]`), then the checkerboard cell size, then the path of a texture.
Below zero the size is rejected (`invalid_length_value`); at zero the object keeps a
plain colour, which is how you write a texture without a checkerboard; above zero the
object becomes a checkerboard. Absent, the field stays at zero.

The texture is a binary PPM (`P6`), 8 bits per channel, and is loaded once per scene
however many objects reference it: the same path yields the same image in memory.

```
sp -3,-0.3,1 2.6 208,56,54 0.85 90        specular only
pl 0,0,0 0,1,0 255,0,225 0 0 2.5          checkerboard, cells of 2.5
sp 0,0,0 2 255,0,0 0.5 40 0.7            checkerboard with specular
cy 0,0,0 0,1,0 1.7 4 96,200,162 0.7 45 0.5
sp 0,0,0 2 255,255,255 0.6 120 0 assets/textures/earth_atmos_2048.ppm
```

A plane line therefore takes 3, 5, 6 or 7 fields, a sphere 3, 5, 6 or 7 as well,
and a cylinder or a cone 5, 7, 8 or 9 — never anything in between.

**Texture paths are resolved from the current working directory.** Launch the
binary from the repository root — `./miniRT_bonus scenes/bonus/presentation.rt` —
or write an absolute path in the scene file. A relative path such as
`assets/textures/earth_atmos_2048.ppm` will not resolve from `scenes/bonus/`,
where it would be looked up as `scenes/bonus/assets/textures/...`, and the scene is
refused with `Bad or missing ppm` on the offending line.

Cells are laid out in surface coordinates, not in world space, so they keep the
same size all around the object:

- **plane** — two in-plane axes divided by the cell size, squares everywhere;
- **cylinder** — arc length around the barrel (`angle x radius`) and height
  along the axis. The number of cells around the circumference is rounded to the
  nearest **even** integer, so the pattern closes on itself: an odd count would
  leave two neighbouring columns of the same colour where the surface wraps, and
  the barrel would show one column twice as wide;
- **sphere** — longitude and latitude, the classic equirectangular mapping.
  Cells are square at the equator and narrow towards the poles, where the
  meridians meet, as on a globe. Longitude is rounded to an even number of
  columns for the same closing reason;
- **cylinder caps** — a plain planar checkerboard in the cap plane, so both ends
  match.

### Scenes shipped

| Path | What it shows |
| --- | --- |
| `scenes/valid/scene.rt` | the three mandatory objects, one spot, shadows |
| `scenes/valid/inside_sphere.rt` | camera inside a sphere, lit from outside |
| `scenes/valid/inside_sphere_light.rt` | camera and light both inside a sphere |
| `scenes/valid/inside_cylinder.rt` | camera inside a closed cylinder |
| `scenes/bonus/presentation.rt` | everything at once: three coloured spots, hard shadows, Phong specular, checkerboards on the plane, a sphere, the cylinder and two cones, one of them tilted |
| `scenes/bonus/vitrine_damier.rt` | seen from above: five spheres standing on dark cells, three cylinders on light ones, mixed checkerboard and plain materials |
| `scenes/bonus/checker.rt` | a single checkerboard floor and a sphere, one raking light |
| `scenes/bonus/checker_multi.rt` | two checkers of different sizes and two coloured spots |
| `scenes/bonus/multi_spot.rt`, `2spot.rt` | coloured and multi-spot lighting |
| `scenes/bonus/multi_spot_cone.rt` | same lighting, the middle sphere replaced by a cone of the same footprint |
| `scenes/bonus/senegal.rt` | the textured Earth framed on Senegal, whole sphere in frame, specular glint on the Atlantic |
| `scenes/bonus/test_plane_texture.rt` | target scene for a textured plane: paved floor and a sphere above it |
| `scenes/bonus/test_cy_texture.rt` | target scene for a textured cylinder: a brick column on a paved floor |
| `scenes/bonus/test_co_texture.rt` | target scene for a textured cone: a diamond-plate cone on a paved floor |
| `scenes/hermes/*.rt` | deliberately broken scenes, one mistake each, used to check the error handling |

### Tests

`tests/` holds a self-contained battery: each `test_*.c` builds against the
project sources and returns a non-zero exit code when an assertion fails. They
cover the parser, the getters, the vector math, the quadratic solver, the line
permutation used by the progressive display, and the render path.

## Resources

Ray tracing and computer graphics:

- Peter Shirley, *Ray Tracing in One Weekend* — the classic gentle introduction
  to a sphere-only ray tracer, and the source of most of the vocabulary used here.
- *Scratchapixel* — https://www.scratchapixel.com — thorough explanations of
  ray-object intersection, shading models and sampling.
- Phong reflection model — ambient, diffuse and specular terms.
- *Physically Based Rendering: From Theory to Implementation* (Pharr, Jakob,
  Humphreys) — for the parts of shading that go beyond this project.
- `man 3 math`, `man 3 pthread`, `man 7 sem_overview` — the C library references
  actually used while writing this code.
- MiniLibX documentation and sources, shipped in `minilibx-linux/`.
- Norm of the 42 school, which shapes the file layout and the function sizes.

### How AI was used

An AI assistant (Hermes) was used as a reviewer and a teacher, never as a code
writer for the project sources:

- reviewing the ray-object intersection code and pointing out arithmetic and
  geometry mistakes, which were then diagnosed and fixed by hand;
- explaining the concepts that were not yet understood — AABB and BVH
  acceleration structures, stratified sampling, the synchronisation protocol
  between the render threads and the display;
- building the headless test harnesses used to measure things that cannot be
  seen on screen: how many lines of the image the permutation misses, how many
  refreshes reach the X server, whether two versions of the renderer produce
  byte-identical images;
- drafting this README and the Doxygen comments, which were then reviewed.

All project code — parser, intersections, shading, threading and display — was
written by hand. Every measurement quoted during the defence can be reproduced
with the harnesses described above.
