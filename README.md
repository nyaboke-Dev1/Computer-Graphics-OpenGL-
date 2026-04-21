Computer Graphics Assignment
Group 11
Members:

Eunice Nyaboke - SCT211-0544/2022

Victor Ireri - SCT211-0435/2023

Task Overview
This assignment consists of two independent problems:

Frame buffer address calculation for a given monitor specification.

OpenGL implementation of a quadrilateral that is translated, then rotated, with specific styling (green border, cream fill) and labelled axes.

1. Frame Buffer Address Calculation
Problem Statement
A system has a 12" × 14" video monitor that displays 120 pixels per inch. Memory is organized in 1‑byte words, the starting frame buffer address is 0, and each pixel uses 4 bits of storage. Find the frame buffer address of the pixel at screen coordinates (x, y).

Solution Explanation
Total pixels in X direction:
Monitor width = 12 inches × 120 pixels/inch = 1440 pixels.
X coordinates range from 0 to 1439.

Total pixels in Y direction:
Monitor height = 14 inches × 120 pixels/inch = 1680 pixels.
Y coordinates range from 0 to 1679 (origin at top‑left or bottom‑left – here we assume standard bottom‑left origin as in OpenGL).

Bits per pixel = 4 bits → 0.5 bytes per pixel.
Therefore, the offset in bytes from the start of the frame buffer is:


​
 
If (y * 1440 + x) is odd, the address is fractional – in practice the frame buffer controller handles pixel pairs, but the formula gives the byte offset.

2. OpenGL Program: Translation + Rotation of a Quadrilateral
Requirements
Original points: A(0,4), B(3,4), C(4,0), D(0,0)

Translation: shift by +2 in X and +2 in Y → new coordinates:
A'(2,6), B'(5,6), C'(6,2), D'(2,2)

Translated figure must have a green border and cream inner shading.

Rotate the translated figure by θ = 55° about the origin.

Display the result with properly labelled and scaled axes.

How We Implemented It (C++/Python OpenGL)
Coordinate Computation

Translation: added tx=2, ty=2 to every vertex.


to each translated vertex (θ = 55°).

Styling

Cream fill: RGB(255, 253, 208) → (1.0, 0.992, 0.816) in OpenGL.

Green border: (0.0, 1.0, 0.0) with line width 2.5.

The polygon is drawn using GL_POLYGON for the fill and GL_LINE_LOOP for the border.

Axes with Labels

X axis from –8 to 8, Y axis from –2 to 10.

Tick marks every 1 unit, numbers drawn using glutBitmapCharacter.

Arrow heads at the positive ends, and letters ‘X’ / ‘Y’.

Reference Shapes (Optional)

Original and translated quadrilaterals are shown as faint dashed lines for context, but the final rotated figure is the only one that satisfies the green‑border + cream‑fill requirement.

Output

The console prints all three sets of coordinates (original, translated, rotated).

The OpenGL window displays the axes and the rotated quadrilateral with the requested colours.

Sample Console Output (Rotated Coordinates)
text
After rotation by 55.0 degrees (about origin):
A''(-2.05, 7.54)  B''(0.64, 8.45)  C''(1.80, 6.06)  D''(-1.47, 5.20)
Running the Program
C++ version:
Compile with -lGL -lGLU -lglut (Linux) or link against freeglut (Windows).

Python version:
Install PyOpenGL and run python quadrilateral.py.

Note: On Windows, the glutCreateWindow call requires a bytes literal without non‑ASCII characters. Use b"..." and avoid the degree symbol in the window title.

