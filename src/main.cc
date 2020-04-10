//
// Created by mehdi on 09/04/2020.
//

#include <GL/glew.h>
#include <GL/gl.h>
#include "marchgl.hh"
#include "marchglew.hh"
#include "marchglut.hh"

int main(int argc, char *argv[])
{
    int width = 1024;
    int height = 512;
    std::string vertex = "../src/vertex.shd";
   // std::string fragment = "../src/fragment.shd";
    std::string fragment = "../src/fragment3.shd";

    MarchGlut glut = MarchGlut(argc, argv, width, height, nullptr);
    glut.init();

    MarchGlew::init();

    MarchGL gl = MarchGL(width, height, vertex, fragment);
    gl.init();
    gl.init_shaders();
    gl.init_vertices();

    glut.linkGL(gl.program_id, gl.vao_id);

    glutMainLoop();

    return 0;
}
