//
// Created by mehdi on 09/04/2020.
//


#include "marchgl.hh"

#include "marcherror.hh"


MarchGL::MarchGL(int width, int height, std::string vertex, std::string fragment) {
    this->width_ = width;
    this->height_ = height;
    this->vertex_ = vertex;
    this->fragment_ = fragment;
}

void MarchGL::init() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, this->width_, this->height_);
    glClearColor(1.0, 0.0, 0.0, 1.0);
    MarchError::test_opengl_error_enum();
}

bool MarchGL::init_shaders() {
    std::string vertex_src = load(this->vertex_);
    std::string fragment_src = load(this->fragment_);
    GLuint shader_id[2];
    GLint compile_status = GL_TRUE;
    char *vertex_shd_src = (char*)std::malloc(vertex_src.length()*sizeof(char));
    char *fragment_shd_src = (char*)std::malloc(fragment_src.length()*sizeof(char));
    vertex_src.copy(vertex_shd_src, vertex_src.length());
    fragment_src.copy(fragment_shd_src,fragment_src.length());


    shader_id[0] = glCreateShader(GL_VERTEX_SHADER); MarchError::test_opengl_error_line();
    shader_id[1] = glCreateShader(GL_FRAGMENT_SHADER);MarchError::test_opengl_error_line();

    glShaderSource(shader_id[0], 1, (const GLchar**)&(vertex_shd_src), 0);MarchError::test_opengl_error_line();
    glShaderSource(shader_id[1], 1, (const GLchar**)&(fragment_shd_src), 0);MarchError::test_opengl_error_line();
    for(int i = 0 ; i < 2 ; i++) {
        glCompileShader(shader_id[i]);MarchError::test_opengl_error_line();
        glGetShaderiv(shader_id[i], GL_COMPILE_STATUS, &compile_status);
        if(compile_status != GL_TRUE) {
            GLint log_size;
            char *shader_log;
            glGetShaderiv(shader_id[i], GL_INFO_LOG_LENGTH, &log_size);
            shader_log = (char*)std::malloc(log_size+1); /* +1 pour le caractere de fin de chaine '\0' */
            if(shader_log != 0) {
                glGetShaderInfoLog(shader_id[i], log_size, &log_size, shader_log);
                std::cerr << "SHADER " << i << ": " << shader_log << std::endl;
                std::free(shader_log);
            }
            std::free(vertex_shd_src);
            std::free(fragment_shd_src);
            glDeleteShader(shader_id[0]);
            glDeleteShader(shader_id[1]);
            return false;
        }
    }
    std::free(vertex_shd_src);
    std::free(fragment_shd_src);


    GLint link_status=GL_TRUE;
    program_id=glCreateProgram();MarchError::test_opengl_error_line();
    if (program_id==0) return false;
    for (int i = 0; i < 2; i++) {
        glAttachShader(program_id, shader_id[i]);MarchError::test_opengl_error_line();
    }
    glLinkProgram(program_id);MarchError::test_opengl_error_line();
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status!=GL_TRUE) {
        GLint log_size;
        char *program_log;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
        program_log = (char*)std::malloc(log_size+1); /* +1 pour le caractere de fin de chaine '\0' */
        if(program_log != 0) {
            glGetProgramInfoLog(program_id, log_size, &log_size, program_log);
            std::cerr << "Program " << program_log << std::endl;
            std::free(program_log);
        }
        glDeleteProgram(program_id);MarchError::test_opengl_error_line();
        glDeleteShader(shader_id[0]);MarchError::test_opengl_error_line();
        glDeleteShader(shader_id[1]);MarchError::test_opengl_error_line();
        program_id=0;
        return false;
    }
    glUseProgram(program_id);MarchError::test_opengl_error_line();
    return true;
}

std::string MarchGL::load(const std::string &filename) {
    std::ifstream input_src_file(filename, std::ios::in);
    std::string ligne;
    std::string file_content;
    if (input_src_file.fail()) {
        std::cerr << "FAIL\n";
        return "";
    }
    while(getline(input_src_file, ligne)) {
        file_content = file_content + ligne + "\n";
    }
    file_content += '\0';
    input_src_file.close();
    return file_content;
}

void MarchGL::init_vertices() {
    GLfloat vertex_list[] = {
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0,
            -1.0, 1.0, 0.0,

            1.0, 1.0, 0.0,
            1.0, -1.0, 0.0,
            -1.0, 1.0, 0.0 }; // (2, 3, 3)
    GLuint vbo_id;
    glGenVertexArrays(1,&vao_id);
    glBindVertexArray(vao_id);
    glGenBuffers(1,&vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER,vbo_id);
    glBufferData(GL_ARRAY_BUFFER, 2*3*3*sizeof(GLfloat), vertex_list , GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    MarchError::test_opengl_error_line();
}