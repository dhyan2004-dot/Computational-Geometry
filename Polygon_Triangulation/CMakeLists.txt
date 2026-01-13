add_executable(main_triangulation main_triangulation.cpp)

target_link_libraries(main_triangulation
    PRIVATE
        CGAL::CGAL
        glfw
        opengl32
)

target_compile_definitions(main_triangulation PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data")
