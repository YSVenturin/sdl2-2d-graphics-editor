# SDL2 2D Graphics Editor

A two-dimensional graphics editor developed in C++ using the SDL2 library.

## Members

* Vinicius Gonçalves Mineira ([@ViniciusG1](https://github.com/ViniciusG1))
* Yuri Sabedot Venturin ([@YSVenturin](https://github.com/YSVenturin))

## Features

The editor allows users to:

* draw lines, rectangles, circles, Bézier curves and polygons;
* fill closed areas using the flood fill algorithm;
* select, delete, move, scale, and rotate objects;
* save the drawing as a BMP file.

## Controls

### Drawing Tools

Tools can be selected by clicking their icons in the sidebar.

* **Line, rectangle, and circle:** click and drag the mouse across the drawing area.
* **Bézier curve:** the first click defines the starting point. On the second click, hold the mouse button and drag to adjust the curve. Release the button to finish.
* **Polygon:** click to add vertices. Click near the first vertex or use the right mouse button to finish the polygon.
* **Flood fill:** select a color and click the area to be filled.

### Selection and Transformations

With the selection tool active:

* click an object to select it;
* click and drag to move the selected object;
* use the mouse wheel to scale it;
* press `Q` or `E` to rotate it;
* press `Delete` or `Backspace` to remove it.

The control points of the selected object are highlighted in orange.

### Other Actions

* `Ctrl + S`: saves the drawing;
* trash button: deletes the selected object;
* clear button: removes all objects and fills;
* save button: saves the drawing.

Drawings are saved as BMP files in the user's `Pictures` directory. The date and time are included in the filename.

## Project Structure

The project follows an object-oriented design. The abstract `Shape` class defines the common operations available for every geometric object:

* drawing;
* translation;
* scaling;
* rotation;
* distance calculation for object selection.

The `Line`, `Rectangle`, `Circle`, `Bezier`, and `Polygon` classes implement these operations according to the characteristics of each shape.

Objects are stored by the `ShapeList` class in a list of `unique_ptr<Shape>`. This structure allows different types of shapes to be stored in the same collection and drawn through polymorphism.

Object selection searches the list in reverse order so that the object displayed above the others is selected first.

## Algorithms

The project uses:

* Bresenham's line algorithm;
* Wu's line algorithm for antialiasing;
* Bresenham's circle algorithm;
* the cubic parametric equation for Bézier curves;
* Euclidean distance for object selection;
* geometric transformations applied to the control points of each object;
* an iterative flood fill algorithm implemented with a stack.

Flood fill results are stored on an auxiliary SDL surface. This means that the algorithm runs only when the tool is used and does not need to be recalculated during every screen update.

## Building and Running

The project is configured for 64-bit Windows using Code::Blocks, MinGW, and SDL2.

1. Extract the entire ZIP file.
2. Open `graphics-editor.cbp` in Code::Blocks.
3. Select the `Debug` build target.
4. Choose **Build and Run**.

The required SDL2 files are included in the `third_party/SDL2` directory, so no additional SDL2 installation should be necessary on Windows.

A compiler with support for C++14 or later is required.
