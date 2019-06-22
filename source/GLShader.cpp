#include "GLPCH.h"

extern uint16 GCountVertexShader ;
extern uint16 GCountPixelShader ;


GLVertexShader::GLVertexShader(void * data, bsize size)
{
	GCountVertexShader++;
	DEBUGFATALERRORGL( Shader = glCreateShader(GL_VERTEX_SHADER));

	GLint glSize = static_cast<GLint>(size);
	GLchar*glData = reinterpret_cast<GLchar*>(data);
	DEBUGFATALERRORGL(glShaderSource(Shader, 1,&glData, &glSize));

	DEBUGFATALERRORGL(glCompileShader(Shader));
	GLint isCompiled = GL_FALSE;
	DEBUGFATALERRORGL(glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled));
	BEAR_ASSERT(isCompiled);
}

GLVertexShader::~GLVertexShader()
{
	GCountVertexShader--;
	DEBUGFATALERRORGL(glDeleteShader(Shader));
}

GLPixelShader::GLPixelShader(void * data, bsize size)
{
	GCountPixelShader++;
	DEBUGFATALERRORGL(Shader = glCreateShader(GL_FRAGMENT_SHADER));

	GLint glSize =static_cast<GLint>( size);
	GLchar*glData = reinterpret_cast<GLchar*>(data);
	DEBUGFATALERRORGL(glShaderSource(Shader, 1, &glData, &glSize));

	DEBUGFATALERRORGL(glCompileShader(Shader));
	GLint isCompiled = GL_FALSE;
	DEBUGFATALERRORGL(glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled));
	BEAR_ASSERT(isCompiled);
}

GLPixelShader::~GLPixelShader()
{
	GCountPixelShader--;
	glDeleteShader(Shader);
}
