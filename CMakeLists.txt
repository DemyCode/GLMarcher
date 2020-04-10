cmake_minimum_required(VERSION 3.15)
project(RayMarcherGL)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS ON)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories(src ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDES_DIRS})

add_executable(RayMarcherGL src/main.cc src/marchgl.cc src/marchglew.cc src/marcherror.cc src/marchglut.cc
        src/utils/vector3.cc)

target_link_libraries(RayMarcherGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})