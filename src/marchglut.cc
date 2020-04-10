//
// Created by mehdi on 09/04/2020.
//



#include "marchglut.hh"

GLuint program_id;
GLuint vao_id;
Vector3 camera_position;
Vector3 camera_target;
Vector3 camera_up;
Vector3 camera_leftv;

void inputs(unsigned char key, int x, int y)
{
    if (key == 'z' || key == 'Z')
        camera_position = camera_position + camera_target;
    if (key == 's' || key == 'S')
        camera_position = camera_position - camera_target;
    if (key == 'q' || key == 'Q')
        camera_position = camera_position - camera_leftv;
    if (key == 'd' || key == 'D')
        camera_position = camera_position + camera_leftv;
    printf(" Touche: %c\n Souris a: %d %d \n", key, x, y);
}

void display() {
    clock_t t = clock();
    GLfloat clock_location = glGetUniformLocation(program_id, "time"); MarchError::test_opengl_error_enum();
    glUniform1f(clock_location, t * 0.001);

    //GAMEPLAY

    GLint position_location = glGetUniformLocation(program_id, "origin"); MarchError::test_opengl_error_enum();
    glUniform3f(position_location, camera_position.x_, camera_position.y_, camera_position.z_);
    GLint target_location = glGetUniformLocation(program_id, "target"); MarchError::test_opengl_error_enum();
    glUniform3f(target_location, camera_target.x_, camera_target.y_, camera_target.z_);
    GLint up_location = glGetUniformLocation(program_id, "upvec"); MarchError::test_opengl_error_enum();
    glUniform3f(up_location, camera_up.x_, camera_up.y_, camera_up.z_);
    GLint leftv_location = glGetUniformLocation(program_id, "leftvec"); MarchError::test_opengl_error_enum();
    glUniform3f(leftv_location, camera_leftv.x_, camera_leftv.y_, camera_leftv.z_);

    glUseProgram(program_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao_id);
    glDrawArrays(GL_TRIANGLES, 0, 3*3);
    glBindVertexArray(0);
    glFinish();
    glutPostRedisplay();
    glutSwapBuffers();
    MarchError::test_opengl_error_enum();
}

void resizer(int width, int height)
{
    glViewport(0, 0, width, height);
    // UNIFORM CREATION
    GLint resolution_location = glGetUniformLocation(program_id, "resolution"); MarchError::test_opengl_error_enum();
    glUniform2f(resolution_location, width, height);
}

MarchGlut::MarchGlut(int argc, char **argv, int width, int height, void (* display)( void )) {
    this->argc_ = argc;
    this->argv_ = argv;
    this->width_ = width;
    this->height_ = height;
    this->display_ = display;
}

void MarchGlut::init() {
    glutInit(&this->argc_, this->argv_);
    glutInitContextVersion(4,5);
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow("Shader Programming");
    glutDisplayFunc(display);
    glutReshapeFunc(resizer);
    glutKeyboardFunc(inputs);
    camera_position = Vector3(0.0, 10.0, 0.0);
    camera_target = Vector3(1.0, 0.0, 0.0);
    camera_up = Vector3(0.0, 1.0, 0.0);
    camera_leftv = camera_target.cross(camera_up).normalize();
}

void MarchGlut::linkGL(GLint program_id_param, GLuint vao_id_param) {
    program_id = program_id_param;
    vao_id = vao_id_param;
    glutDisplayFunc(display);
}