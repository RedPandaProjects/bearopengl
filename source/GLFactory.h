#pragma once
class GLFactory:public BearRHI::BearRHIFactory
{
public:
	GLFactory();
	virtual BearRHI::BearRHIInterface*CreateInterface();
	virtual void DestroyInterface(BearRHI::BearRHIInterface*a);

	virtual BearRHI::BearRHIDefaultManager*CreateDefaultManager();
	virtual void DestroyDefaultManager(BearRHI::BearRHIDefaultManager*a);

	virtual BearRHI::BearRHIRenderTargetView*CreateRenderTargetView( bsize w, bsize h, BearGraphics::BearRenderTargetFormat format);
	virtual void DestroyRenderTargetView(BearRHI::BearRHIRenderTargetView*a);

	virtual BearRHI::BearRHIViewport*CreateViewport(void*win, bsize w, bsize h, bool fullscreen, bool vsync);
	virtual void DestroyViewport(BearRHI::BearRHIViewport*a);

	virtual BearRHI::BearRHITexture2D*CreateTexture2D(bsize w, bsize h, bsize mip, BearGraphics::BearTexturePixelFormat format, bool dynamic, void*data);
	virtual void DestroyTexture2D(BearRHI::BearRHITexture2D*a);

	virtual BearRHI::BearRHITexture2DArray*CreateTexture2DArray(bsize w, bsize h, bsize depth, bsize mip, BearGraphics::BearTexturePixelFormat format, void*data);
	virtual void DestroyTexture2DArray(BearRHI::BearRHITexture2DArray*a);

	virtual BearRHI::BearRHIVertexBuffer*CreateVertexBuffer( void*data, bsize size, bool dynamic);
	virtual void DestroyVertexBuffer(BearRHI::BearRHIVertexBuffer*a);

	virtual BearRHI::BearRHIIndexBuffer*CreateIndexBuffer(void*data, bsize size, bool dynamic);
	virtual void DestroyIndexBuffer(BearRHI::BearRHIIndexBuffer*a);

	virtual BearRHI::BearRHIVertexShader *CreateVertexShader(void*data, bsize size);
	virtual void DestroyVertexShader(BearRHI::BearRHIVertexShader*a);

	virtual BearRHI::BearRHIPixelShader *CreatePixelShader(void*data, bsize size);
	virtual void DestroyPixelShader(BearRHI::BearRHIPixelShader*a);

	virtual BearRHI::BearRHIVertexShaderCompiler *CreateVertexShaderCompiler();
	virtual void DestroyVertexShaderCompiler(BearRHI::BearRHIVertexShaderCompiler*a);

	virtual BearRHI::BearRHIPixelShaderCompiler *CreatePixelShaderCompiler();
	virtual void DestroyPixelShaderCompiler(BearRHI::BearRHIPixelShaderCompiler*a);

	virtual BearRHI::BearRHIVertexState* CreateVertexState(const BearGraphics::BearVertexStateInitializer&initializer, void*data, bsize size);
	virtual void DestroyVertexState(BearRHI::BearRHIVertexState*a);

	virtual BearRHI::BearRHIDepthStencilView*CreateDepthStencilView(bsize w, bsize h, BearGraphics::BearDepthStencilFormat format);
	virtual void DestroyDepthStencilView(BearRHI::BearRHIDepthStencilView*a);

	virtual BearRHI::BearRHIDepthStencilState*CreateDepthStencilState(const BearGraphics::BearDepthStencilStateInitializer&initializer);
	virtual void DestroyDepthStencilState(BearRHI::BearRHIDepthStencilState*a);
	
	virtual BearRHI::BearRHISamplerState*CreateSamplerState(const BearGraphics::BearSamplerStateInitializer&initializer);
	virtual void DestroySamplerState(BearRHI::BearRHISamplerState*a);

	virtual BearRHI::BearRHIBlendState*CreateBlendState(const BearGraphics::BearBlendStateInitializer&initializer);
	virtual void DestroyBlendState(BearRHI::BearRHIBlendState*a);

	virtual BearRHI::BearRHIRasterizerState*CreateRasterizerState(const BearGraphics::BearRasterizerStateInitializer&initializer);
	virtual void DestroyRasterizerState(BearRHI::BearRHIRasterizerState*a);

	virtual BearRHI::BearRHIShaderConstants*CreateShaderConstants(const BearGraphics::BearShaderConstantsInitializer&initializer, bool dynamic);
	virtual void DestroyShaderConstants(BearRHI::BearRHIShaderConstants*a);

	~GLFactory();
	
private:
};

