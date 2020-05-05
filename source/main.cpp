//
// Created by Erwan on 05-May-20.
//

#include <cmath>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Shader.h>
#include <Program.h>
#include <GL/glew.h>

/** data to load on the GPU, it represent a square using homogeneous coordinate **/
GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
};

static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

int main(int ac, char **av) {
    const int width = 500;
    const int height = 500;

    /** Window and OpenGL context creation **/
    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(width, height, "minimalOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    /** Load OpenGL function pointers using glew **/
    glewExperimental = GL_TRUE;
    glewInit();

    /** Load shaders and create drawing program **/
    Shader vertexShader("shaders/vertex.glsl", Shader::Vertex);
    Shader fragmentShader("shaders/fragment.glsl", Shader::Fragment);
    Program program;

    program.addShader(vertexShader);
    program.addShader(fragmentShader);
    program.link();

    /** Create buffer object and load our data **/
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /** Setting up the OpenGL program input parameters **/
    glVertexAttribPointer(glGetAttribLocation(program.getProgramID(), "point"), 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    /** Set the viewport to the size of the window **/
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    /** Main loop, just drawing a square each frame **/
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program.getProgramID());
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glfwSwapBuffers(window);
    }

    return 0;
}