#ifndef CEFOFFSCREEN_GL_CORE_HH
#define CEFOFFSCREEN_GL_CORE_HH

#include "GL/glew.h"

class GLCore {
private:
	GLuint _prog;
	GLint _posLoc;
	GLint _texcoordLoc;
	GLint _texLoc;
	GLint _mvpLoc;

	static const float _vertices[];
	static const float _texcoords[];
	static const unsigned short _indices[];

public:

private:
	static GLuint compileShaderFromCode(GLenum shader_type, const char *src);
	static GLuint compileShaderFromFile(GLenum shader_type, const char *filepath);

	static GLuint createShaderProgram(const char *vert, const char *frag);
	static GLuint createShaderProgram(GLuint vert, GLuint frag);

	static bool deleteShader(GLuint shader);
	static bool deleteProgram(GLuint program);

public:
	GLCore();
	bool init(unsigned int w, unsigned int h);
    void destroy();

    GLuint getProg() const;
    GLint getPosLoc() const;
    GLint getTexcoordLoc() const;
    GLint getTexLoc() const;
    GLint getMvpLoc() const;
	static unsigned int getNbIndices();
	static const float *getVertices();
	static const float *getTexCoords();
	static const unsigned short *getIndices();

};

#endif //CEFOFFSCREEN_GL_CORE_HH