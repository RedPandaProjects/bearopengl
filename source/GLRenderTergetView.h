#pragma once
class GLTexture2D;
class GLRenderTergetView :public BearRHI::BearRHIRenderTargetView
{
public:
	GLRenderTergetView(bsize w, bsize h,BearGraphics::BearRenderTargetFormat format);
	virtual void Resize(bsize w, bsize h);
	virtual void ClearColor(const BearCore::BearColor&color);
	virtual bptr GetRenderTarget();
	virtual void  GenerateMips();
	~GLRenderTergetView();
	GLTexture2D*Texture;
private:
	BearGraphics::BearRenderTargetFormat Format;


};

