#include <fstream>
#include <iostream>
#include "GLCore.hh"

// 2 3
// 0 1
const float GLCore::_vertices[] = {
        -1, -1, 0,
        1, -1, 0,
        -1, 1, 0,
        1, 1, 0,
};

const float GLCore::_texcoords[] = {
        0, 1,
        1, 1,
        0, 0,
        1, 0,
};

const unsigned short GLCore::_indices[] = {
        0, 1, 3,
        0, 3, 2,
};

GLuint GLCore::compileShaderFromCode(GLenum shader_type, const char *src) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE) {
        return shader;
    }

    // shader compile fail!
    std::cerr << "shader compilation error" << std::endl;

    GLint info_len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
    if (info_len > 1) {
        char *info_log = (char *) malloc(sizeof(char) * info_len);
        glGetShaderInfoLog(shader, info_len, NULL, info_log);
        std::cerr << "Error compiling shader: " << info_log << std::endl;
        free(info_log);
    }
    glDeleteShader(shader);
    return 0;
}

GLuint GLCore::compileShaderFromFile(GLenum shader_type, const char *filepath) {
    std::ifstream ifs(filepath);
    std::string shader_str((std::istreambuf_iterator<char>(ifs)),
                           (std::istreambuf_iterator<char>()));

    const char *src = shader_str.data();
    return compileShaderFromCode(shader_type, src);
}

bool GLCore::deleteShader(GLuint shader) {
    glDeleteShader(shader);
    return true;
}

GLuint GLCore::createShaderProgram(const char *vert, const char *frag) {
    GLuint vertShader = compileShaderFromFile(GL_VERTEX_SHADER, vert);
    GLuint fragShader = compileShaderFromFile(GL_FRAGMENT_SHADER, frag);
    if (vertShader == 0 || fragShader == 0) {
        return 0;
    }
    return createShaderProgram(vertShader, fragShader);
}

GLuint GLCore::createShaderProgram(GLuint vert, GLuint frag) {
    GLuint program = glCreateProgram();

    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    glDetachShader(program, vert);
    glDetachShader(program, frag);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked) {
        return program;
    }

    // fail...
    GLint info_len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
    if (info_len > 1) {
        char *info_log = (char *) malloc(sizeof(char) * info_len);
        glGetProgramInfoLog(program, info_len, NULL, info_log);
        std::cerr << "Error linking program: " << info_log << std::endl;
        free(info_log);
    }

    glDeleteProgram(program);
    return 0;
}

bool GLCore::deleteProgram(GLuint program) {
    glDeleteProgram(program);
    return true;
}

GLCore::GLCore() {

}

bool GLCore::init(unsigned int w, unsigned int h) {
    // shader
    this->_prog = GLCore::createShaderProgram("shaders/tex.vert", "shaders/tex.frag");
    if (this->_prog == 0) {
        std::cerr << "Shader compilation failed!" << std::endl;
        return (true);
    }

    this->_posLoc = glGetAttribLocation(this->_prog, "a_position");
    this->_texcoordLoc = glGetAttribLocation(this->_prog, "a_texcoord");
    this->_texLoc = glGetUniformLocation(this->_prog, "s_tex");
    this->_mvpLoc = glGetUniformLocation(this->_prog, "u_mvp");

    // initial GL state
    glViewport(0, 0, w, h);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    return (false);
}

GLuint GLCore::getProg() const {
    return (this->_prog);
}

GLint GLCore::getPosLoc() const {
    return (this->_posLoc);
}

GLint GLCore::getTexcoordLoc() const {
    return (this->_texcoordLoc);
}

GLint GLCore::getTexLoc() const {
    return (this->_texLoc);
}

GLint GLCore::getMvpLoc() const {
    return (this->_mvpLoc);
}

void GLCore::destroy() {
    GLCore::deleteProgram(this->_prog);
    this->_prog = 0;
}

unsigned int GLCore::getNbIndices() {
    return (sizeof(GLCore::_indices) / sizeof(GLCore::_indices[0]));
}

const float *GLCore::getVertices() {
    return (GLCore::_vertices);
}

const float *GLCore::getTexCoords() {
    return (GLCore::_texcoords);
}

const unsigned short *GLCore::getIndices() {
    return (GLCore::_indices);
}
