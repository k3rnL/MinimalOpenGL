//
// Created by Erwan on 05-May-20.
//

#include <cmath>
#include <cstdio>
#include <GL/glew.h>
#include <GL/glut.h>
#include <Shader.h>
#include <Program.h>

GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
};

GLuint g_programID;

int main(int ac, char **av) {
    const int width = 500;
    const int height = 500;

    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutReportErrors();
    glutCreateWindow("minimalOpenGL");

    glewExperimental = GL_TRUE;
    glewInit();

    Shader vertexShader("shaders/vertex.glsl", Shader::Vertex);
    Shader fragmentShader("shaders/fragment.glsl", Shader::Fragment);
    Program program;

    program.addShader(vertexShader);
    program.addShader(fragmentShader);
    program.link();

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(glGetAttribLocation(program.getProgramID(), "point"), 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(0);

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    g_programID = program.getProgramID();
    glutDisplayFunc([](){
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(g_programID);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glutSwapBuffers();
    });

    glutMainLoop();
    return 0;
}