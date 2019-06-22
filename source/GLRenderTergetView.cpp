#include "GLPCH.h"
extern uint16 GCountRenderTarger;
extern BearCore::BearMutex GRenderTargerMutex;
extern 	GLuint GlobalRenderTarget;
GLRenderTergetView::GLRenderTergetView(bsize w, bsize h, BearGraphics::BearRenderTargetFormat format):Texture(0), Format(format)
{

	GCountRenderTarger++;
	Resize(w, h);
}

void GLRenderTergetView::Resize(bsize w, bsize h)
{
	if (Texture)BearCore::bear_delete(Texture);
	Texture = BearCore::bear_new<GLTexture2D>(w, h, Format);
}

void GLRenderTergetView::ClearColor(const BearCore::BearColor & color)
{
	BearCore::BearMutexLock lock(GRenderTargerMutex);
 	DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, GlobalRenderTarget));
	DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_COLOR_ATTACHMENT0, Texture->Texture, 0));
	DEBUGFATALERRORGL(glDrawBuffer(GL_COLOR_ATTACHMENT0));
	DEBUGFATALERRORGL(glClearColor(color.GetFloat()[0], color.GetFloat()[1], color.GetFloat()[2], color.GetFloat()[3]));
	DEBUGFATALERRORGL(glClear(GL_COLOR_BUFFER_BIT));
}

bptr GLRenderTergetView::GetRenderTarget()
{
	return static_cast<bptr>(0);
}

void GLRenderTergetView::GenerateMips()
{
}

GLRenderTergetView::~GLRenderTergetView()
{
	BearCore::bear_delete(Texture);
	GCountRenderTarger--;
}
