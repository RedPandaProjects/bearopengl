#pragma once
#include "BearRHI.h"
#pragma warning(disable:4005)
#include "OpenGL.h"
#include "GLFactory.h"
#include "GLStats.h"
#include "GLInterface.h"
#include "GLViewport.h"
#include "GLRenderTergetView.h"
#include "GLDepthStencilView.h"
#include "GLBuffer.h"
#include "GLTexture2D.h"
#include "GLTexture2DArray.h"
#include "GLShader.h"
#include "GLShaderCompiler.h"
#include "GLShaderConstants.h"
#include "GLDefaultManager.h"
inline bool GLCheakError()
{
	GLenum err(glGetError());
	bool berror = true;
	if (err != GL_NO_ERROR) {
		const bchar*error = TEXT("UNKOWN");;
		berror = false;
		switch (err) {
		case GL_INVALID_OPERATION:      error = TEXT("INVALID_OPERATION");      break;
		case GL_INVALID_ENUM:           error = TEXT("INVALID_ENUM");            break;
		case GL_INVALID_VALUE:          error = TEXT("INVALID_VALUE");          break;
		case GL_OUT_OF_MEMORY:          error = TEXT("OUT_OF_MEMORY");           break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = TEXT("INVALID_FRAMEBUFFER_OPERATION");   break;
		}
		BearCore::BearLog::Printf(TEXT("OpenGL ошибка:" BEAR_PRINT_CURRENT), error);
		err = glGetError();
	}
	return berror;
}
#define FATALERRORGL(exp) {exp;BEAR_RASSERT(GLCheakError());}
#ifdef DEBUG
#define DEBUGFATALERRORGL(exp) FATALERRORGL(exp)
#else
#define DEBUGFATALERRORGL(exp) {exp;}
#endif

extern GLFactory *Factory;