#include "GLPCH.h"
PFNGLDRAWBUFFERSPROC glDrawBuffers;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNGLSTENCILFUNCSEPARATEATIPROC glStencilFuncSeparate;
PFNGLSTENCILOPSEPARATEATIPROC glStencilOpSeparate;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
PFNGLGETSTRINGIPROC glGetStringi;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
PFNGLCLEARBUFFERFVPROC glClearBufferfv;
PFNGLTEXSTORAGE2DPROC	glTexStorage2D;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample;
PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
PFNGLDELETEFRAMEBUFFERSPROC  glDeleteFramebuffers;
PFNGLGENSAMPLERSPROC glGenSamplers;
PFNGLDELETESAMPLERSPROC glDeleteSamplers;
PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;
PFNGLBINDSAMPLERPROC glBindSampler;
PFNGLENABLEIPROC glEnablei;
PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei;
PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei;
PFNGLBLENDFUNCIPROC glBlendFunci;
PFNGLBLENDEQUATIONIPROC glBlendEquationi;
PFNGLDISABLEIPROC glDisablei;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
PFNGLCOLORMASKIPROC glColorMaski;
PFNGLBLENDEQUATIONPROC glBlendEquation;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
PFNGLTEXSTORAGE3DPROC glTexStorage3D;
PFNGLTEXIMAGE3DPROC glTexImage3D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;
PFNGLTEXSUBIMAGE3DEXTPROC glTexSubImage3D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;
PFNGLDEPTHRANGEFPROC glDepthRangef;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
//PFNGLFWPOLLEVENTSPROC glfwPollEvents;
bool GetFunction()
{

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if (!wglChoosePixelFormatARB)
	{
		return false;
	}

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if (!wglCreateContextAttribsARB)
	{
		return false;
	}

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (!wglSwapIntervalEXT)
	{
		return false;
	}

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if (!glAttachShader)
	{
		return false;
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if (!glBindBuffer)
	{
		return false;
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if (!glBindVertexArray)
	{
		return false;
	}

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if (!glBufferData)
	{
		return false;
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if (!glCompileShader)
	{
		return false;
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if (!glCreateProgram)
	{
		return false;
	}

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if (!glCreateShader)
	{
		return false;
	}

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if (!glDeleteBuffers)
	{
		return false;
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if (!glDeleteProgram)
	{
		return false;
	}

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if (!glDeleteShader)
	{
		return false;
	}

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if (!glDeleteVertexArrays)
	{
		return false;
	}

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if (!glDetachShader)
	{
		return false;
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if (!glEnableVertexAttribArray)
	{
		return false;
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if (!glGenBuffers)
	{
		return false;
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if (!glGenVertexArrays)
	{
		return false;
	}

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	if (!glGetAttribLocation)
	{
		return false;
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if (!glGetProgramInfoLog)
	{
		return false;
	}

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if (!glGetProgramiv)
	{
		return false;
	}

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if (!glGetShaderInfoLog)
	{
		return false;
	}

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if (!glGetShaderiv)
	{
		return false;
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if (!glLinkProgram)
	{
		return false;
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if (!glShaderSource)
	{
		return false;
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if (!glUseProgram)
	{
		return false;
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if (!glVertexAttribPointer)
	{
		return false;
	}

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if (!glBindAttribLocation)
	{
		return false;
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if (!glGetUniformLocation)
	{
		return false;
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if (!glUniformMatrix4fv)
	{
		return false;
	}

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if (!glActiveTexture)
	{
		return false;
	}

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if (!glUniform1i)
	{
		return false;
	}

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if (!glGenerateMipmap)
	{
		return false;
	}

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if (!glDisableVertexAttribArray)
	{
		return false;
	}

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if (!glUniform3fv)
	{
		return false;
	}

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if (!glUniform4fv)
	{
		return false;
	}
	glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");
	if (!glGetStringi)
	{
		return false;
	}
	glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEATIPROC)wglGetProcAddress("glStencilFuncSeparate");
	if (!glStencilFuncSeparate)
	{
		return false;
	}
	glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)wglGetProcAddress("glStencilOpSeparate");
	if (!glStencilOpSeparate)
	{
		return false;
	}

	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
	if (!glGenFramebuffers)
	{
		return false;
	}

	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
	if (!glGenFramebuffers)
	{
		return false;
	}
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
	if (!glGenFramebuffers)
	{
		return false;
	}
	glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)wglGetProcAddress("glClearBufferfv");
	if (!glGenFramebuffers)
	{
		return false;
	}
	glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)wglGetProcAddress("glTexStorage2D");
	if (!glTexStorage2D)
	{
		return false;
	}
	glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)wglGetProcAddress("glTexStorage2DMultisample");
	if (!glTexStorage2DMultisample)
	{
		return false;
	}
	glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
	if (!glDeleteFramebuffers)
	{
		return false;
	}
	glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)wglGetProcAddress("glTexImage2DMultisample");
	if (!glTexImage2DMultisample)
	{
		return false;
	}
	glGenSamplers = (PFNGLGENSAMPLERSPROC)wglGetProcAddress("glGenSamplers");
	if (!glGenSamplers)
	{
		return false;
	}
	glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)wglGetProcAddress("glDeleteSamplers");
	if (!glDeleteSamplers)
	{
		return false;
	}
	glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)wglGetProcAddress("glSamplerParameteri");
	if (!glSamplerParameteri)
	{
		return false;
	}
	glBindSampler = (PFNGLBINDSAMPLERPROC)wglGetProcAddress("glBindSampler");
	if (!glBindSampler)
	{
		return false;
	}
	glEnablei = (PFNGLENABLEIPROC)wglGetProcAddress("glEnablei");
	if (!glEnablei)
	{
		return false;
	}
	glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)wglGetProcAddress("glBlendFuncSeparatei");
	if (!glBlendFuncSeparatei)
	{
		return false;
	}
	glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)wglGetProcAddress("glBlendEquationSeparatei");
	if (!glBlendEquationSeparatei)
	{
		return false;
	}
	glBlendFunci = (PFNGLBLENDFUNCIPROC)wglGetProcAddress("glBlendFunci");
	if (!glBlendFunci)
	{
		return false;
	}
	glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)wglGetProcAddress("glBlendEquationi");
	if (!glBlendEquationi)
	{
		return false;
	}
	glDisablei = (PFNGLDISABLEIPROC)wglGetProcAddress("glDisablei");
	if (!glDisablei)
	{
		return false;
	}
	glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)wglGetProcAddress("glBlendFuncSeparate");
	if (!glBlendFuncSeparate)
	{
		return false;
	}
	glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)wglGetProcAddress("glBlendEquationSeparate");
	if (!glBlendEquationSeparate)
	{
		return false;
	}
	glColorMaski = (PFNGLCOLORMASKIPROC)wglGetProcAddress("glColorMaski");
	if (!glColorMaski)
	{
		return false;
	}
	glBlendEquation = (PFNGLBLENDEQUATIONPROC)wglGetProcAddress("glBlendEquation");
	if (!glBlendEquation)
	{
		return false;
	}
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	if (!glUniform1f)
	{
		return false;
	}
	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	if (!glUniform2f)
	{
		return false;
	}
	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	if (!glUniform3f)
	{
		return false;
	}
	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	if (!glUniform4f)
	{
		return false;
	}
	glDrawBuffers = (PFNGLDRAWBUFFERSPROC)wglGetProcAddress("glDrawBuffers");
	if (!glDrawBuffers)
	{
		return false;
	}
	glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)wglGetProcAddress("glFramebufferTexture");
	if (!glFramebufferTexture)
	{
		return false;
	}
	glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
	if (!glCheckFramebufferStatus)
	{
		return false;
	}
	glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
	if (!glGenRenderbuffers)
	{
		return false;
	}
	glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
	if (!glBindRenderbuffer)
	{
		return false;
	}
	glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
	if (!glRenderbufferStorage)
	{
		return false;
	}
	glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
	if (!glFramebufferRenderbuffer)
	{
		return false;
	}
	glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
	if (!glDeleteRenderbuffers)
	{
		return false;
	}
	glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)wglGetProcAddress("glTexStorage3D");
	if (!glTexStorage3D)
	{
		return false;
	}
	glTexImage3D = (PFNGLTEXIMAGE3DPROC)wglGetProcAddress("glTexImage3D");
	if (!glTexImage3D)
	{
		return false;
	}
	glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)wglGetProcAddress("glCompressedTexImage2D");
	if (!glCompressedTexImage2D)
	{
		return false;
	}
	glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)wglGetProcAddress("glCompressedTexImage3D");
	if (!glCompressedTexImage3D)
	{
		return false;
	}
	glTexSubImage3D = (PFNGLTEXSUBIMAGE3DEXTPROC)wglGetProcAddress("glTexSubImage3D");
	if (!glTexSubImage3D)
	{
		return false;
	}
	glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)wglGetProcAddress("glCompressedTexSubImage2D");
	if (!glCompressedTexSubImage2D)
	{
		return false;
	}
	glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)wglGetProcAddress("glCompressedTexSubImage3D");
	if (!glCompressedTexSubImage3D)
	{
		return false;
	}
	glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)wglGetProcAddress("glCompressedTexImage1D");
	if (!glCompressedTexImage1D)
	{
		return false;
	}
	glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)wglGetProcAddress("glCompressedTexSubImage1D");
	if (!glCompressedTexSubImage1D)
	{
		return false;
	}
	glDepthRangef = (PFNGLDEPTHRANGEFPROC)wglGetProcAddress("glDepthRangef");
	if (!glDepthRangef)
	{
		return false;
	}
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	if (!glBufferSubData)
	{
		return false;
	}
	glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)wglGetProcAddress("glVertexAttribIPointer");
	if (!glVertexAttribIPointer)
	{
		return false;
	}
	return true;
}