#include <stdio.h>
#include <iostream>
#include "utils/Logger.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint shaderProgram;
GLuint shaderProgram2;
GLuint VAO;
GLuint VAO2;

void init(void) {
    // create and compile vertex shader
    const char *vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n";
    
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        Logger::logerr("Error compiling vertex shader: ");
        GLchar infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        printf("%s", infoLog);
    }

    // create and compile fragment shader
    const char *fragmentShaderSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n";

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        Logger::logerr("Error compiling fragment shader: ");
        GLchar infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        printf("%s", infoLog);
    }
    // create and compile secound fragment shader
    const char *fragmentShaderSource2 = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n";

    GLuint fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &status);
    if (!status) {
        Logger::logerr("Error compiling fragment shader: ");
        GLchar infoLog[1024];
        glGetShaderInfoLog(fragmentShader2, 1024, NULL, infoLog);
        printf("%s", infoLog);
    }

    // create and link shader program
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status) {
        Logger::logerr("Error linking program:");
        GLchar infoLog[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        printf("%s", infoLog);
    }

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &status);
    if (!status) {
        Logger::logerr("Error linking program:");
        GLchar infoLog[1024];
        glGetProgramInfoLog(shaderProgram2, 1024, NULL, infoLog);
        printf("%s", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDeleteShader(fragmentShader2);

    // create triangle buffer
    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        //-0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, // top left
    };
    GLuint indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    float trigVertices[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.6f, 0.0f
    };

    //VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(float), 
        (void*)0
    );
    glEnableVertexAttribArray(0);
    //VBO2
    GLuint VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trigVertices), trigVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(float), 
        (void*)0
    );
    glEnableVertexAttribArray(0);

    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);
    //VAO2
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trigVertices), trigVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    //EBO
/*  GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
*/
}

void draw(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0 , 3);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0, width, height);
}

int main(void) {
    Logger::log("Welcome to OpenGL Odyssey!");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(1024, 768, "OpenGL Odyssey", NULL, NULL);
    if (!window)
    {
        Logger::logerr("Failed to create Window");
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewInit();

    init();

    // set line or fill from graphic
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here
        draw();

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}