#pragma once
class GLViewport:public BearRHI::BearRHIViewport
{
public:
	GLViewport(void*win, bsize w, bsize h,bool fullscreen, bool vsync);
	virtual void Swap() ;
	virtual void SetFullScreen(bool fullscreen);
	virtual void Resize(bsize w, bsize h);
	virtual void SetVsync(bool vsync);
	virtual void ClearColor(const BearCore::BearColor&color);
	virtual void ClearDepth(float depth);
	virtual void ClearStencil(uint8 mask);
	~GLViewport();
	virtual bptr GetRenderTarget();
	GLDepthStencilContainer  CurrentDepthStencilContainer;
	uint32 CurrentStencilRef; 
	GLBlendContainer CurrentBlendContainer[8];
	GLRasterizerContainer CurrentRasterizerContainer;
#ifdef WINDOWS
	void MakeCurrent();
private:
	HDC DeviceContext;
	HGLRC RenderContext;
	void*WindowHandle;
#endif 

private:
	BearCore::BearVector2<bsize> m_screen_size;
	bool m_fullsceen;
	GLuint VertexArray;


};

