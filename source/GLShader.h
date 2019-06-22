#pragma once
class GLVertexShader :public BearRHI::BearRHIVertexShader
{
public:
	GLVertexShader(void*data, bsize size);
	~GLVertexShader();
	GLuint Shader;
};

#pragma once
class GLPixelShader :public BearRHI::BearRHIPixelShader
{
public:
	GLPixelShader(void*data,bsize size);
	~GLPixelShader();
	GLuint Shader;
};

