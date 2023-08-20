cmake_minimum_required(VERSION 3.0.0)

project(my_opengl_project VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLUT)

add_executable(my_opengl_project src/main.cpp
    src/glut.h
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lGL -lGLU -lglut -L /usr/lib/nvidia-331/")
target_link_libraries(
    ${PROJECT_NAME}
    ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARIES})

target_link_libraries(my_opengl_project glfw
    GL)
target_link_libraries(my_opengl_project GLU)
