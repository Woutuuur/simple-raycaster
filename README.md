# Simple raycaster
A simple ray caster in made in C++ with SDL2

Requires SDL2. Compile using `make`.
The `options.h` file can be changed (before compilation) to either increase/decrease the amount of rays and the FOV of the camer, among other parameters. 

The map files contain of the following values:
- Two values representing the initial player X and Y position (in px)
- Two values representing the width and height of the map.
- A matrix of 1's and 0's representing either a wall or empty space respectively.
