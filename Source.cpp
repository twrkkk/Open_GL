#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <glut.h>
#include <GL/glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/transform.hpp>

// 
#include <stdio.h>
#include <iostream>


const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 rotation;

void main()
{
    gl_Position = rotation * vec4(aPos, 1.0);
    color = aColor;
}

)";

const char* fragmentShaderSource = R"(
#version 330 core

in vec3 color;

out vec4 fragColor;

void main()
{
    fragColor = vec4(color, 1.0);
}
)";

int main()
{
    // �������������� GLFW
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    // ������� ����
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    // ������� �������� OpenGL � ����������� ��� � ����
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);

    // �������������� GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return 1;
    }


    // ������ ������ ��� ������������
    GLfloat vertices[] = {
       0.0f,  0.5f, 0.0f, // ������� 
       0.8f, 0.2f, 0.8f, // ���� �����
      -0.5f, -0.5f, 0.0f, // ������� 
       0.2f, 0.2f, 0.2f, // ����
       0.5f, -0.5f, 0.0f, // ������� 
       0.2f, 0.2f, 0.6f  // ���� 
    };




    // ������� ����� ������ � ��������� ���
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ������� ��������� ���������
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    // ��������� �������� ������ � ������� ������
    GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "aColor");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));



    // �������� ���� ����������
    while (!glfwWindowShouldClose(window)) {
        // ������� �����
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4  model(1.0f);
        //glm::mat4 rotation = glm::rotate(glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::translate(model, glm::vec3(0.3f, -0.3f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        GLuint rotationLoc = glGetUniformLocation(shaderProgram, "rotation");
        glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ��������� ������ �������, ����� ��� ��������� �����
        glfwPollEvents();

        // �������� ��, ��� �� ����������, �� �������
        glfwSwapBuffers(window);
    }

    // ������� ����� ������ � ��������� ���������
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ��������� ���� � ��������� ������ GLFW
    glfwTerminate();

    return 0;
}



//while (!glfwWindowShouldClose(window)) {
    //    // ������� �����
    //    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    // �������� ������ �������, ����� ��� ��������� �����
    //    glfwPollEvents();
    //    // ��������� ��, ��� �� ��������, �� �������
    //    glfwSwapBuffers(window);
    //}