#include "GLPCH.h"
extern uint16 GCountDepthStencilView;
extern BearCore::BearMutex GRenderTargerMutex;
extern 	GLuint GlobalRenderTarget;
extern BearCore::BearMutex GBufferMutex;

GLDepthStencilView::GLDepthStencilView(bsize w, bsize h, BearGraphics::BearDepthStencilFormat format) :Texture(0), Format(format)
{
	GCountDepthStencilView++;
	Resize(w, h);
}

void GLDepthStencilView::Resize(bsize w, bsize h)
{
	if (Texture)BearCore::bear_delete(Texture);
	Texture = BearCore::bear_new<GLTexture2D>(w, h, Format);
}

void GLDepthStencilView::ClearDepth(float depth)
{
	BearCore::BearMutexLock lock(GRenderTargerMutex);
	BearCore::BearMutexLock lock_buffer(GBufferMutex);
	GLInterface::MakeCurrent();

	DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, GlobalRenderTarget));
	switch (Format)
	{
	case BearGraphics::DSF_DEPTH16:
		DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Texture->Texture, 0));
		break;
	case BearGraphics::DSF_DEPTH32F:
		DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Texture->Texture, 0));
		break;
	case BearGraphics::DSF_DEPTH24_STENCIL8:
		DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_DEPTH_ATTACHMENT, Texture->Texture, 0));
		DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_STENCIL_ATTACHMENT, Texture->Texture, 0));
		break;
	case BearGraphics::DSF_DEPTH32F_STENCIL8:
		DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_DEPTH_STENCIL_ATTACHMENT, Texture->Texture, 0));
		break;
	default:
		break;
	}

	DEBUGFATALERRORGL(glClearDepth(depth));
	DEBUGFATALERRORGL(glClear(GL_DEPTH_BUFFER_BIT));

}

void GLDepthStencilView::ClearStencil(uint8 mask)
{
	BearCore::BearMutexLock lock(GRenderTargerMutex);
	DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, GlobalRenderTarget));
	switch (Format)
	{
	case BearGraphics::DSF_DEPTH16:
		return;
	case BearGraphics::DSF_DEPTH32F:
		return;
		break;
	case BearGraphics::DSF_DEPTH24_STENCIL8:
		DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_DEPTH_STENCIL_ATTACHMENT, Texture->Texture, 0));
		DEBUGFATALERRORGL(glDrawBuffer(GL_DEPTH_STENCIL_ATTACHMENT));
		break;
	case BearGraphics::DSF_DEPTH32F_STENCIL8:
		DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_DEPTH_STENCIL_ATTACHMENT, Texture->Texture, 0));
		DEBUGFATALERRORGL(glDrawBuffer(GL_DEPTH_STENCIL_ATTACHMENT));
		break;
	default:
		break;
	}

	DEBUGFATALERRORGL(glClearStencil(mask));
	DEBUGFATALERRORGL(glClear(GL_STENCIL_BUFFER_BIT));
}

bool GLDepthStencilView::IsStencil() const
{
	switch (Format)
	{
	case BearGraphics::DSF_DEPTH16:
	case BearGraphics::DSF_DEPTH32F:
		return false;
	case BearGraphics::DSF_DEPTH24_STENCIL8:
	case BearGraphics::DSF_DEPTH32F_STENCIL8:
		return true;
	}
	return false;
}

GLDepthStencilView::~GLDepthStencilView()
{
	GCountDepthStencilView--;
	if (Texture)BearCore::bear_delete(Texture);
}
