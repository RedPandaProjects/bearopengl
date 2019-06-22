#pragma once
class GLShaderConstants :public BearRHI::BearRHIShaderConstants
{
public:
	GLShaderConstants(const BearGraphics::BearShaderConstantsInitializer&initializer, bool dynamic);
	~GLShaderConstants();
	virtual void*Lock();
	virtual void Unlock();	
	static bsize GetSize(BearGraphics::BearConstantFormat format);
	bsize Size;
	void *Data;
	bool Update;
	BearCore::BearVector <BearGraphics::BearConstantFormat> Constants;
private:
};
