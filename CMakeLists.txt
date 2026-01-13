cmake_minimum_required(VERSION 3.15)
project(Polygon_Triangulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CGAL CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(polygon_generator)
add_subdirectory(main_triangulation)
