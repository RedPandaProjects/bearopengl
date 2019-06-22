#pragma once
class GLTexture2D:public BearRHI::BearRHITexture2D
{
public:
	GLTexture2D(bsize w, bsize h, bsize mip, BearGraphics::BearTexturePixelFormat format, bool dynamic, void*data);
	//FOR RenderTarget
	GLTexture2D(bsize w, bsize h, BearGraphics::BearRenderTargetFormat format);
	//FOR DepthStencill
	GLTexture2D(bsize w, bsize h, BearGraphics::BearDepthStencilFormat format);
	virtual void*Lock( bsize mipId);
	virtual void Unlock();
	virtual void GenerateMipmap();

	bool isDynamic()const;
	bool isRenderTarget()const;
	bool isDepthStencill()const;
	~GLTexture2D();
	GLuint Texture;
	
private:
	BearGraphics::BearTexturePixelFormat m_Format;
	BearCore::BearVector2<bsize> m_Size;
	bsize m_MipID;
	void* m_Data;
	bool m_IsDynamic;
	bool m_is_renderTarget;
	bool m_is_depthStencill;
};

