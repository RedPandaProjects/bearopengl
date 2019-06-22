#pragma once
class GLDefaultManager :public BearRHI::BearRHIDefaultManager
{
public:
	GLDefaultManager();
	virtual const bchar*GetPixelShader(BearGraphics::BearDefaultPixelShader type) ;
	virtual const bchar*GetVertexShader(BearGraphics::BearDefaultVertexShader type);
	~GLDefaultManager();
private:

};
