# Polygon Generator (C++)

This repository contains a C++ implementation of a **polygon generation utility**, built using **CMake**. The program generates polygonal geometries based on specified parameters and is intended for use in computational geometry, graphics, or simulation workflows.

---

## Project Overview

The objective of this project is to provide a lightweight and modular C++ program for generating polygons programmatically. The implementation emphasizes:

- Clear separation between build configuration and source code
- Standard C++ practices
- Portability across platforms using CMake

---

## Repository Contents
```
.
├── CMakeLists.txt # CMake build configuration
├── polygon_generator.cpp # Main C++ source file
└── README.md # Project documentation
```


---

## Requirements

- C++ compiler supporting C++11 or later  
  (e.g., GCC, Clang, MSVC)
- CMake (version 3.10 or higher recommended)

---

## Build Instructions

Follow the steps below to build the project using CMake:

1. Create a build directory inside the project root
2. Configure the project using CMake
3. Build the executable

After successful compilation, an executable will be generated in the build directory.

---

## Usage

Once built, run the generated executable from the command line.  
The program generates polygon data based on the logic implemented in `polygon_generator.cpp`.

Further customization can be done by modifying:
- Input parameters
- Polygon generation logic
- Output formatting

Refer to comments within the source file for implementation details.

---

## Code Structure

- **polygon_generator.cpp**  
  Contains the core logic for polygon generation, including:
  - Definition of polygon vertices
  - Geometry construction logic
  - Output or visualization hooks (if applicable)

- **CMakeLists.txt**  
  Defines:
  - Project name
  - Compiler settings
  - Build targets

---

## Applications

This project can be extended or integrated into:
- Computational geometry pipelines
- Mesh generation workflows
- Graphics or visualization systems
- Numerical simulations requiring polygonal domains

---

## Author

Dhyan G  
Dual Degree (B.Tech + M.Tech)  
Aerospace Engineering & Computational Engineering  
Indian Institute of Technology Madras  



