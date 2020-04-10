//
// Created by mehdi on 09/04/2020.
//

#ifndef POGLTEMPLATE_GLUT_HH
#define POGLTEMPLATE_GLUT_HH

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>


#include <utils/vector3.hh>
#include <marcherror.hh>

class MarchGlut {
public:
    MarchGlut(int argc, char **argv, int width, int height, void (*display)(void));
    void init();
    void launch();
    void linkGL(GLint program_id, GLuint vao_id);

private:
    int argc_;
    char **argv_;
    int width_;
    int height_;

    void (*display_)(void);
};


#endif //POGLTEMPLATE_GLUT_HH
