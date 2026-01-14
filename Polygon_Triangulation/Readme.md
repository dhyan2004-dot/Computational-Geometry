# Polygon Triangulation (C++)

This repository contains a C++ implementation for **polygon triangulation**, built using **CMake**. The project focuses on decomposing a polygon into a set of non-overlapping triangles, a fundamental operation in computational geometry with applications in graphics, meshing, and numerical simulations.

---

## Project Overview

Triangulation is the process of dividing a polygon into triangles such that:
- No triangles overlap
- The union of all triangles exactly covers the polygon
- Triangle vertices coincide with polygon vertices

This project provides a standalone C++ program that performs polygon triangulation and demonstrates the algorithmic workflow clearly and modularly.

---

## Repository Contents

```
.
├── CMakeLists.txt # CMake build configuration
├── main_triangulation.cpp # Main C++ source file for triangulation
└── README.md # Project documentation
```

---

## Requirements

- C++ compiler supporting **C++11 or later**
  - GCC / Clang / MSVC
- **CMake** version 3.10 or higher (recommended)

---

## Build Instructions

To build the project using CMake:

1. Create a separate build directory inside the project root  
2. Configure the project using CMake  
3. Compile the source code  

After a successful build, an executable for polygon triangulation will be generated in the build directory.

---

## Usage

Run the generated executable from the command line.

The program:
- Defines a polygon using a sequence of vertices
- Applies a triangulation algorithm
- Outputs the resulting triangles (format depends on implementation)

Input polygon definition and triangulation logic can be modified directly inside `main_triangulation.cpp`.

---

## Code Description

### `main_triangulation.cpp`

This file contains:
- Representation of polygon vertices
- Core triangulation logic (e.g., ear clipping or similar method)
- Validation of polygon geometry
- Output of triangulated elements

The file is internally commented to explain key geometric and algorithmic steps.

### `CMakeLists.txt`

Responsible for:
- Defining the project and executable
- Setting compiler standards
- Managing the build process in a platform-independent manner

---

## Applications

Polygon triangulation is widely used in:
- Computational geometry
- Mesh generation for CFD and FEM
- Computer graphics and rendering
- Collision detection
- GIS and spatial analysis

This implementation serves as a base that can be extended for more advanced meshing or geometry-processing tasks.

---

## Author

Dhyan G  
Dual Degree (B.Tech + M.Tech)  
Aerospace Engineering & Computational Engineering  
Indian Institute of Technology Madras  

