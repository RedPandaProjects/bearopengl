#include "GLPCH.h"
extern BearCore::BearMutex GMutexTexture;
extern uint16 GCountTexture;


GLTexture2D::GLTexture2D(bsize w, bsize h, bsize mip, BearGraphics::BearTexturePixelFormat format, bool dynamic, void * data) :m_is_renderTarget(false), m_Format(format), m_Data(0), m_is_depthStencill(false), m_IsDynamic(dynamic)
{
	BearCore::BearMutexLock lock(GMutexTexture);
	DEBUGFATALERRORGL(glGenTextures(1, &Texture));
	m_Size.set(w, h);
	DEBUGFATALERRORGL(glBindTexture(GL_TEXTURE_2D, Texture));
	DEBUGFATALERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(mip - 1)));
	for (bsize a = 0; a < mip; a++)
	{
		bsize w_ = GetMip(w, a);
		bsize h_ = GetMip(h, a);
		if (isCompressor(format))
		{
			DEBUGFATALERRORGL(glCompressedTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(a), GLInterface::TranslatePixelFormatI(format), static_cast<GLsizei>(w_), static_cast<GLsizei>(h_), 0, static_cast<GLsizei>(GetSizeDepth(w_, h_, format)), data));
		}
		else
		{
			DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(a), GLInterface::TranslatePixelFormatI(format), static_cast<GLsizei>(w_), static_cast<GLsizei>(h_), 0, GLInterface::TranslatePixelFormat(format), GLInterface::TranslatePixelType(format), data));
		}
		if (data)
			data = (uint8*)data + GetSizeDepth(w_, h_, format);
	}
	DEBUGFATALERRORGL(glBindTexture(GL_TEXTURE_2D, 0));
	GCountTexture++;
}

GLTexture2D::GLTexture2D(bsize w, bsize h, BearGraphics::BearRenderTargetFormat format) :m_is_renderTarget(true), m_is_depthStencill(false), m_Data(0)
{
	BearCore::BearMutexLock lock(GMutexTexture);
	DEBUGFATALERRORGL(	glGenTextures(1, &Texture));
	DEBUGFATALERRORGL(glBindTexture(GL_TEXTURE_2D, Texture));
	switch (format)
	{
	case BearGraphics::RTF_R8:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D,0, GL_R8, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0,GL_R,GL_UNSIGNED_BYTE, 0));
		break;
	case BearGraphics::RTF_R8G8:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_RG, GL_UNSIGNED_BYTE, 0));
		break;
	case BearGraphics::RTF_R8G8B8A8:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0));
		break;
	case BearGraphics::RTF_R32F:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_R, GL_FLOAT, 0));
		break;
	case BearGraphics::RTF_R32G32F:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_RG, GL_FLOAT, 0));
		break;
	case BearGraphics::RTF_R32G32B32F:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_RGB, GL_FLOAT, 0));
		break;
	case BearGraphics::RTF_R32G32B32A32F:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_RGBA, GL_FLOAT, 0));
		break;
	default:
		BEAR_RASSERT(false);
	}
	DEBUGFATALERRORGL(glBindTexture(GL_TEXTURE_2D, 0));
	GCountTexture++;
}

GLTexture2D::GLTexture2D(bsize w, bsize h, BearGraphics::BearDepthStencilFormat format) :m_is_renderTarget(false), m_is_depthStencill(true), m_Data(0)
{
	BearCore::BearMutexLock lock(GMutexTexture);
	DEBUGFATALERRORGL(glGenTextures(1, &Texture));
	DEBUGFATALERRORGL(glBindTexture(GL_TEXTURE_2D, Texture));	GCountTexture++;
	switch (format)
	{
	case BearGraphics::DSF_DEPTH16:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0));
		DEBUGFATALERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT));
		break;
	case BearGraphics::DSF_DEPTH32F:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0));
		DEBUGFATALERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT));
		break;
	case BearGraphics::DSF_DEPTH24_STENCIL8:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0));
		DEBUGFATALERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT));
		break;
	case BearGraphics::DSF_DEPTH32F_STENCIL8:
		DEBUGFATALERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_DEPTH_STENCIL, GL_FLOAT, 0));
		DEBUGFATALERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT));
		break;
	default:
		break;
	}

}

void * GLTexture2D::Lock(bsize mipId)
{
	BEAR_ASSERT(!m_is_renderTarget && !m_is_depthStencill);
	m_MipID = mipId;
	m_Data = BearCore::bear_alloc<uint8>(GetSizeDepth(GetMip(m_Size.x, mipId), GetMip(m_Size.y, mipId), m_Format));
	return m_Data;
}

void GLTexture2D::Unlock()
{
	BEAR_ASSERT(!m_is_renderTarget && !m_is_depthStencill);
	bsize w = GetMip(m_Size.x, m_MipID);
	bsize h = GetMip(m_Size.y, m_MipID);
	if (isCompressor(m_Format))
	{
		DEBUGFATALERRORGL(glCompressedTexSubImage2D(GL_TEXTURE_2D, static_cast<GLint>(m_MipID), 0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h), GLInterface::TranslatePixelFormat(m_Format), static_cast<GLsizei>(GetSizeDepth(w,h,m_Format)), m_Data));
	}
	else
	{
		DEBUGFATALERRORGL(glTexSubImage2D(GL_TEXTURE_2D, static_cast<GLint>(m_MipID), 0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h), GLInterface::TranslatePixelFormat(m_Format), GLInterface::TranslatePixelType(m_Format), m_Data));
	}
	if (m_Data)BearCore::bear_free(m_Data);

}

void GLTexture2D::GenerateMipmap()
{
	DEBUGFATALERRORGL(glGenerateMipmap(GL_TEXTURE_2D));
}

bool GLTexture2D::isDynamic() const
{
	return m_IsDynamic;
}

bool GLTexture2D::isRenderTarget() const
{
	return m_is_renderTarget;
}

bool GLTexture2D::isDepthStencill() const
{
	return m_is_depthStencill;
}

GLTexture2D::~GLTexture2D()
{
	if (m_Data)BearCore::bear_free(m_Data);
	GCountTexture--;
	DEBUGFATALERRORGL(glDeleteTextures(1, &Texture));
}
