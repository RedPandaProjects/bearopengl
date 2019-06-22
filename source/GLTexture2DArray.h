#pragma once
class GLTexture2DArray:public BearRHI::BearRHITexture2DArray
{
public:
	GLTexture2DArray(bsize w, bsize h,bsize depth, bsize mip, BearGraphics::BearTexturePixelFormat format, void*data);
	virtual void*Lock(bsize DepthId, bsize mipId);
	virtual void Unlock();
	virtual void GenerateMipmap();
	~GLTexture2DArray();
private:

};

