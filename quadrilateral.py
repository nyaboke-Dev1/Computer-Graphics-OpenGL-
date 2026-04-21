#DONE BY GROUP 11
#SCT211-0435/2023
#SCT211-0544/2022

#python quadrilateral.py


#!/usr/bin/env python3
# OpenGL Program: Translation + Rotation of a Quadrilateral (Python version)
#
# Initial points: A(0,4), B(3,4), C(4,0), D(0,0)
# Translation: +2 in X, +2 in Y  →  A'(2,6), B'(5,6), C'(6,2), D'(2,2)
#
# INSTRUCTION (ii): The translated figure is drawn with a GREEN border and CREAM inner shading.
# INSTRUCTION (iii): The translated figure is then rotated by 55° about the origin; the rotated figure is shown.
#
# Axes are drawn with labelled tick marks and 'X'/'Y' labels.

import sys
import math
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

# ---------- Data ----------
# Original quadrilateral
original = [
    [0.0, 4.0],   # A
    [3.0, 4.0],   # B
    [4.0, 0.0],   # C
    [0.0, 0.0]    # D
]

translated = [[0.0, 0.0] for _ in range(4)]
rotated   = [[0.0, 0.0] for _ in range(4)]

tx, ty = 2.0, 2.0
theta_deg = 55.0
theta_rad = math.radians(theta_deg)

# ---------- Transformation functions ----------
def compute_translated():
    for i in range(4):
        translated[i][0] = original[i][0] + tx
        translated[i][1] = original[i][1] + ty

def compute_rotated():
    cos_t = math.cos(theta_rad)
    sin_t = math.sin(theta_rad)
    for i in range(4):
        x = translated[i][0]
        y = translated[i][1]
        rotated[i][0] = x * cos_t - y * sin_t
        rotated[i][1] = x * sin_t + y * cos_t

# ---------- Drawing helpers ----------
def draw_polygon(vertices, fill_rgb, border_rgb, line_width=2.0):
    """Draw a filled polygon with a border."""
    # Fill
    glColor3f(*fill_rgb)
    glBegin(GL_POLYGON)
    for v in vertices:
        glVertex2f(v[0], v[1])
    glEnd()
    # Border
    glColor3f(*border_rgb)
    glLineWidth(line_width)
    glBegin(GL_LINE_LOOP)
    for v in vertices:
        glVertex2f(v[0], v[1])
    glEnd()

def draw_string(x, y, text):
    """Render a string at (x,y) using bitmap font."""
    glRasterPos2f(x, y)
    for ch in text:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ord(ch))

def draw_axes_with_labels():
    """Draw X and Y axes with tick marks, numbers, and labels."""
    glColor3f(0.8, 0.8, 0.8)   # light gray
    glLineWidth(1.5)

    # Axes lines
    glBegin(GL_LINES)
    glVertex2f(-8.0, 0.0)
    glVertex2f( 8.0, 0.0)
    glVertex2f( 0.0, -2.0)
    glVertex2f( 0.0, 10.0)
    glEnd()

    # Arrow heads (simple triangles)
    glBegin(GL_TRIANGLES)
    # X arrow
    glVertex2f(7.8,  0.15)
    glVertex2f(8.0,  0.0)
    glVertex2f(7.8, -0.15)
    # Y arrow
    glVertex2f(-0.15, 9.8)
    glVertex2f( 0.0, 10.0)
    glVertex2f( 0.15, 9.8)
    glEnd()

    # Tick marks and numbers
    # X axis ticks -7 .. 7 (except 0)
    for x in range(-7, 8):
        if x == 0:
            continue
        glBegin(GL_LINES)
        glVertex2f(x, -0.1)
        glVertex2f(x,  0.1)
        glEnd()
        draw_string(x - 0.2, -0.5, str(x))

    # Y axis ticks -1 .. 9 (except 0)
    for y in range(-1, 10):
        if y == 0:
            continue
        glBegin(GL_LINES)
        glVertex2f(-0.1, y)
        glVertex2f( 0.1, y)
        glEnd()
        draw_string(0.15, y - 0.15, str(y))

    # Origin tick and label
    glBegin(GL_LINES)
    glVertex2f(-0.1, 0.0)
    glVertex2f( 0.1, 0.0)
    glVertex2f( 0.0, -0.1)
    glVertex2f( 0.0,  0.1)
    glEnd()
    draw_string(-0.35, -0.5, "0")

    # Axis labels 'X' and 'Y'
    draw_string(7.6, -0.6, "X")
    draw_string(0.15, 9.7, "Y")

# ---------- GLUT callbacks ----------
def display():
    glClear(GL_COLOR_BUFFER_BIT)

    # Draw axes
    draw_axes_with_labels()

    # ----- Original shape (faint dashed, for reference) -----
    glEnable(GL_LINE_STIPPLE)
    glLineStipple(1, 0x00FF)   # dashed pattern
    glColor3f(0.5, 0.5, 0.5)
    glLineWidth(1.0)
    glBegin(GL_LINE_LOOP)
    for v in original:
        glVertex2f(v[0], v[1])
    glEnd()
    glDisable(GL_LINE_STIPPLE)

    # ----- INSTRUCTION (ii): Translated figure with GREEN border and CREAM fill -----
    # Cream colour: RGB(255, 253, 208) -> (1.0, 0.992, 0.816)
    draw_polygon(translated,
                 fill_rgb=(1.0, 0.992, 0.816),
                 border_rgb=(0.0, 1.0, 0.0),
                 line_width=2.5)

    # ----- INSTRUCTION (iii): Rotated figure (55° from translated) -----
    # No specific styling requested – using red border + light peach fill for visibility
    draw_polygon(rotated,
                 fill_rgb=(1.0, 0.9, 0.8),
                 border_rgb=(1.0, 0.0, 0.0),
                 line_width=2.0)

    glutSwapBuffers()

def reshape(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    # World coordinates: x ∈ [-8, 8], y ∈ [-2, 10]
    gluOrtho2D(-8.0, 8.0, -2.0, 10.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

def print_coordinates():
    print("===== Coordinate Information =====")
    print("Original points:")
    print(f"A({original[0][0]:.2f}, {original[0][1]:.2f})  "
          f"B({original[1][0]:.2f}, {original[1][1]:.2f})  "
          f"C({original[2][0]:.2f}, {original[2][1]:.2f})  "
          f"D({original[3][0]:.2f}, {original[3][1]:.2f})")

    print(f"\nAfter translation by ({tx:.1f}, {ty:.1f}):")
    print(f"A'({translated[0][0]:.2f}, {translated[0][1]:.2f})  "
          f"B'({translated[1][0]:.2f}, {translated[1][1]:.2f})  "
          f"C'({translated[2][0]:.2f}, {translated[2][1]:.2f})  "
          f"D'({translated[3][0]:.2f}, {translated[3][1]:.2f})")

    print(f"\nAfter rotation by {theta_deg:.1f} degrees (about origin):")
    print(f"A''({rotated[0][0]:.2f}, {rotated[0][1]:.2f})  "
          f"B''({rotated[1][0]:.2f}, {rotated[1][1]:.2f})  "
          f"C''({rotated[2][0]:.2f}, {rotated[2][1]:.2f})  "
          f"D''({rotated[3][0]:.2f}, {rotated[3][1]:.2f})")
    print("==================================")

# ---------- Main ----------
def main():
    compute_translated()
    compute_rotated()
    print_coordinates()

    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
    glutInitWindowSize(800, 600)
    # Use an ASCII‑only bytes literal – no degree symbol
    glutCreateWindow(b"OpenGL: Translation + Rotation (55 deg) with Labeled Axes (Python)")

    glClearColor(0.1, 0.1, 0.15, 1.0)
    glutDisplayFunc(display)
    glutReshapeFunc(reshape)
    glutMainLoop()

if __name__ == "__main__":
    main()