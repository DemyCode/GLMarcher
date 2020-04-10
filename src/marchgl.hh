//
// Created by mehdi on 09/04/2020.
//

#ifndef POGLTEMPLATE_GL_HH
#define POGLTEMPLATE_GL_HH

#include <GL/glew.h>
#include <GL/gl.h>
#include <fstream>

class MarchGL {
public:
    MarchGL(int width, int height, std::string string, std::string basicString);
    void init();
    bool init_shaders();
    void init_vertices();

    GLint program_id;
    GLuint vao_id;

private:
    int width_;
    int height_;
    std::string vertex_;
    std::string fragment_;

    static std::string load(const std::string &filename);
};


#endif //POGLTEMPLATE_GL_HH
