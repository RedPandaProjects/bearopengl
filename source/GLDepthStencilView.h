#pragma once
class GLDepthStencilView:public BearRHI::BearRHIDepthStencilView
{
public:
	GLDepthStencilView(bsize w, bsize h,BearGraphics::BearDepthStencilFormat format);
	virtual void Resize(bsize w, bsize h) ;
	virtual void ClearDepth(float depth);
	virtual void ClearStencil(uint8 mask);
	bool IsStencil()const;
	~GLDepthStencilView();
	GLTexture2D*Texture;
private:
	BearGraphics::BearDepthStencilFormat Format;
};

