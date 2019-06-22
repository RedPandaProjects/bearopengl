#include "GLPCH.h"
extern uint16 GCountVertexShaderCompiler;
extern uint16 GCountPixelShaderCompiler;

static bool TestPixelShader(const bchar8*text, GLint size, BearCore::BearString&str)
{
	GLint shader;
	DEBUGFATALERRORGL(shader = glCreateShader(GL_FRAGMENT_SHADER));
	DEBUGFATALERRORGL(glShaderSource(shader, 1, &text, &size));

	DEBUGFATALERRORGL(glCompileShader(shader));
	GLint isCompiled = GL_FALSE;
	DEBUGFATALERRORGL(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		DEBUGFATALERRORGL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));
		BearCore::BearVector<GLchar> infoLog; infoLog.resize(maxLength);
		DEBUGFATALERRORGL(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));

		str.append(*BearCore::BearEncoding::ToCurrent(&infoLog[0], &infoLog[0] + maxLength));
		DEBUGFATALERRORGL(glDeleteShader(shader));
		return false;
	}
	DEBUGFATALERRORGL(glDeleteShader(shader));
	return true;
}
static bool TestVertexShader(const bchar8*text, GLint size, BearCore::BearString&str)
{
	GLint shader;
	DEBUGFATALERRORGL(shader= glCreateShader(GL_VERTEX_SHADER));
	DEBUGFATALERRORGL( glShaderSource(shader, 1, &text, &size));

	DEBUGFATALERRORGL(glCompileShader(shader));
	GLint isCompiled = GL_FALSE;
	DEBUGFATALERRORGL(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		DEBUGFATALERRORGL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));
		BearCore::BearVector<GLchar> infoLog; infoLog.resize(maxLength);
		DEBUGFATALERRORGL(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));

		str.append(*BearCore::BearEncoding::ToCurrent(&infoLog[0], &infoLog[0] + maxLength));
		DEBUGFATALERRORGL(glDeleteShader(shader));
		return false;
	}
	DEBUGFATALERRORGL(glDeleteShader(shader));
	return true;
}


GLVertexShaderCompiler::GLVertexShaderCompiler():Text(0)
{
	GCountVertexShaderCompiler++;
}

bool GLVertexShaderCompiler::CompileFromText(const bchar * text, BearCore::BearString & out_error)
{
	if (Text)BearCore::bear_free(Text);
	Text=BearCore::BearString::Duplicate(*BearCore::BearEncoding::ToANSI(text));
	return TestVertexShader(Text,static_cast<GLint>( BearCore::BearString::GetSize(text)), out_error);
}

void * GLVertexShaderCompiler::GetPointerBuffer()
{
	return (void*)Text;
}

bsize GLVertexShaderCompiler::GetSizeBuffer()
{
	return BearCore::BearString::GetSize(Text);
}

GLVertexShaderCompiler::~GLVertexShaderCompiler()
{
	if (Text)BearCore::bear_free(Text);
	GCountVertexShaderCompiler--;
}

GLPixelShaderCompiler::GLPixelShaderCompiler() :Text(0)
{
	GCountPixelShaderCompiler++;

}

bool GLPixelShaderCompiler::CompileFromText(const bchar * text, BearCore::BearString & out_error)
{

	if (Text)BearCore::bear_free(Text);
	Text = BearCore::BearString::Duplicate(*BearCore::BearEncoding::ToANSI(text));
	return TestPixelShader(Text, static_cast<GLint>(BearCore::BearString::GetSize(text)), out_error);
}

void * GLPixelShaderCompiler::GetPointerBuffer()
{
	return (void*)Text;
}

bsize GLPixelShaderCompiler::GetSizeBuffer()
{
	return BearCore::BearString::GetSize(Text);
}

GLPixelShaderCompiler::~GLPixelShaderCompiler()
{
	if (Text)BearCore::bear_free(Text);
	GCountPixelShaderCompiler--;
}
