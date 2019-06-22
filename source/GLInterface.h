#pragma once
class GLInterface:public BearRHI::BearRHIInterface
{
public:
	GLInterface();
	virtual void Clear();
	virtual void AttachViewport( BearRHI::BearRHIViewport*render_target);
	virtual void AttachRenderTargetView(uint32 id, BearRHI::BearRHIRenderTargetView*render_target) ;
	virtual void AttachDepthStencilView(BearRHI::BearRHIDepthStencilView*depthStencill) ;
	virtual void DetachRenderTargetView(uint32 id);
	virtual void DetachDepthStencilView();
	virtual void DetachViewport();

	virtual void SetViewport( float x, float y, float width, float height, float minDepth = 0.f, float maxDepth = 1.f) ;
	virtual void SetScissor( bool  enable,float x, float y, float x1, float y1) ;

	virtual void SetPixelShader(BearRHI::BearRHIPixelShader*shader);
	virtual void SetVertexShader(BearRHI::BearRHIVertexShader*shader);

	virtual void SetIndexBuffer(BearRHI::BearRHIIndexBuffer*buffer) ;
	virtual void SetVertexBuffer(BearRHI::BearRHIVertexBuffer*buffer) ;

	virtual void SetVertexState(BearRHI::BearRHIVertexState*buffer);
	virtual void SetBlendState(BearRHI::BearRHIBlendState*State, const  BearCore::BearColor&color);;
	virtual void SetDepthStencilState(BearRHI::BearRHIDepthStencilState*State,uint32 StenciRef);
	virtual void SetRasterizerState(BearRHI::BearRHIRasterizerState*State);

	virtual void SetVertexShaderConstants(bsize slot, BearRHI::BearRHIShaderConstants*constants);
	virtual void SetVertexShaderResource(bsize slot, BearRHI::BearRHITexture2D*texture2d, BearRHI::BearRHISamplerState*sampler);

	virtual void SetPixelShaderConstants(bsize slot, BearRHI::BearRHIShaderConstants*constants);
	virtual void SetPixelShaderResource(bsize slot, BearRHI::BearRHITexture2D*texture2d, BearRHI::BearRHISamplerState*sampler);


	virtual void Draw(bsize size, bsize possition, BearGraphics::BearDrawType mode);
	~GLInterface();
	static GLint  TranslatePixelFormat(BearGraphics::BearTexturePixelFormat px);
	static GLint  TranslatePixelType(BearGraphics::BearTexturePixelFormat px);
	static GLint  TranslatePixelFormatI(BearGraphics::BearTexturePixelFormat px);
	void			InitializePlatform();
	void			DestroyPlatform();
	static bool  	IsSupport();
#ifdef WINDOWS
	static HWND WindowHandle;
	static HDC DeviceContext;
	static HGLRC RenderContext;
	static HGLRC CreateRenderContext(HDC Device);
	static void MakeCurrent();
#endif

	static GLVertexState *VertexState;
private:
	BearRHI::BearRHIRenderTargetView * RenderTargetViewArray[8];
	BearRHI::BearRHIViewport * Viewport;
	BearRHI::BearRHIDepthStencilView* DepthStencilView;


	GLRasterizerState*RasterizerState;
	GLDepthStencilState*DepthStencilState;
	uint32 DepthStencilState_StencilRef;
	GLBlendState*BlendState;

	GLBlendContainer m_CurrentBlendContainer[8];
	void UpdateBlendState(GLBlendContainer*BlendContainer);
	GLDepthStencilContainer  m_CurrentDepthStencilContainer;
	uint32 m_CurrentStencilRef;
	void UpdateDepthStencilState(GLDepthStencilContainer*DepthStencilContainer, uint32 StencilRef);
	GLRasterizerContainer m_RasterizerContainer;
	void UpdateRasterizerState(GLRasterizerContainer*RasterizerContainer);

	GLuint VertexArray;
	GLuint VertexBuffer;
	GLuint IndexBuffer;

	bool m_UpdateRenderTarget;
private:
	BearCore::BearFVector2 m_viewport;
};

