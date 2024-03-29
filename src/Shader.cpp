#include "shader/Shader.hpp"

Shader::Shader() {
    
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexSource;
    std::string fragmentSource;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    // ensure ifstream objects can throw exceptions:
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        // open files
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        //read file's buffer contents into streams
        std::stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // close files
        vertexShaderFile.close();
        fragmentShaderFile.close();

        //convert stream into string
        vertexSource = vertexShaderStream.str();
        fragmentSource = fragmentShaderStream.str();
    }
    catch(std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << '\n' << std::endl;
    }
    
    const char* vertexShaderSource = vertexSource.c_str();
    const char* fragmentShaderSource = fragmentSource.c_str();

    GLuint vertexShader, fragmentShader;
    GLint status;
    GLchar infoLog[1024];
    
    // create and compile vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // create and compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // create and link shader program
    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAMM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shaders after linking no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::createShader(const char* vertexPath, const char* fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexSource;
    std::string fragmentSource;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    // ensure ifstream objects can throw exceptions:
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        // open files
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        //read file's buffer contents into streams
        std::stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // close files
        vertexShaderFile.close();
        fragmentShaderFile.close();

        //convert stream into string
        vertexSource = vertexShaderStream.str();
        fragmentSource = fragmentShaderStream.str();
    }
    catch(std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << '\n' << std::endl;
    }
    
    const char* vertexShaderSource = vertexSource.c_str();
    const char* fragmentShaderSource = fragmentSource.c_str();

    GLuint vertexShader, fragmentShader;
    GLint status;
    GLchar infoLog[1024];
    
    // create and compile vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // create and compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // create and link shader program
    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAMM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shaders after linking no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}