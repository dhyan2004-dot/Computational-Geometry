# Computational Geometry (C++)

This repository contains a collection of **C++ implementations of fundamental computational geometry algorithms**, organized into modular subprojects and built using **CMake**. Each subproject focuses on a specific geometric task and is designed to be self-contained, clear, and extensible.

The repository is intended for academic learning, algorithmic experimentation, and as a foundation for geometry-based simulation, graphics, and meshing workflows.

---

## Repository Overview

The project is structured into independent modules, each addressing a core computational geometry problem.

```
computational-geometry/
│
├── Polygon_Generator/
│ ├── CMakeLists.txt
│ ├── polygon_generator.cpp
│ └── README.md
│
├── Polygon_Triangulation/
│ ├── CMakeLists.txt
│ ├── main_triangulation.cpp
│ └── README.md
│
├── CMakeLists.txt
├── .gitattributes
└── README.md
```

---

## Modules

### 1. Polygon Generator

The **Polygon Generator** module provides a C++ utility for generating polygonal geometries programmatically. It serves as a basic building block for downstream geometry-processing tasks.

**Key features:**
- Programmatic generation of polygon vertices
- Simple and modular C++ implementation
- CMake-based build system

Refer to `Polygon_Generator/README.md` for detailed documentation.

---

### 2. Polygon Triangulation

The **Polygon Triangulation** module implements polygon triangulation, decomposing a polygon into a set of non-overlapping triangles. This is a fundamental operation in computational geometry.

**Key features:**
- Polygon representation using vertex lists
- Triangulation logic implemented in C++
- Suitable for meshing, graphics, and numerical simulations

Refer to `Polygon_Triangulation/README.md` for algorithm details and usage instructions.

---

## Build System

- The repository uses **CMake** for cross-platform builds.
- Each module has its own `CMakeLists.txt`.
- A top-level `CMakeLists.txt` is provided to manage or extend multi-module builds if required.

---

## Requirements

- C++ compiler supporting **C++11 or later**
  - GCC, Clang, or MSVC
- **CMake** version 3.10 or higher (recommended)

---

## Usage

Each module can be built and run independently by navigating to the corresponding directory and following the instructions in its README file.

This modular design allows:
- Independent testing of algorithms
- Easy extension with additional geometry modules
- Clean separation of concerns

---

## Applications

The algorithms and utilities in this repository are applicable to:
- Computational geometry education
- Mesh generation for CFD and FEM
- Computer graphics and rendering
- Geometry preprocessing for simulations
- Algorithm prototyping and research

---

## Author

Dhyan G  
Dual Degree (B.Tech + M.Tech)  
Aerospace Engineering & Computational Engineering  
Indian Institute of Technology Madras  
