#pragma once
class GLVertexShaderCompiler:public BearRHI::BearRHIVertexShaderCompiler
{
public:
	GLVertexShaderCompiler();
	virtual bool CompileFromText(const bchar*text, BearCore::BearString&out_error) ;
	virtual void*GetPointerBuffer();
	virtual bsize GetSizeBuffer() ;
	~GLVertexShaderCompiler();
private:
	const bchar8*Text;
};

class GLPixelShaderCompiler :public BearRHI::BearRHIPixelShaderCompiler
{
public:
	GLPixelShaderCompiler();
	virtual bool CompileFromText(const bchar*text, BearCore::BearString&out_error);
	virtual void*GetPointerBuffer();
	virtual bsize GetSizeBuffer();
	~GLPixelShaderCompiler();
private:
	const bchar8*Text;
};

