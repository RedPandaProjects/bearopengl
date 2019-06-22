#include "GLPCH.h"

GLTexture2DArray::GLTexture2DArray(bsize w, bsize h, bsize depth, bsize mip, BearGraphics::BearTexturePixelFormat format, void * data)
{
}

void * GLTexture2DArray::Lock(bsize DepthId, bsize mipId)
{
	return nullptr;
}

void GLTexture2DArray::Unlock()
{
}

void GLTexture2DArray::GenerateMipmap()
{
}

GLTexture2DArray::~GLTexture2DArray()
{
}
