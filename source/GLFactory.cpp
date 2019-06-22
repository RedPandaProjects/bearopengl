#include "GLPCH.h"

using namespace BearCore;

GLFactory::GLFactory()
{
}

BearRHI::BearRHIInterface * GLFactory::CreateInterface()
{
	return bear_new<GLInterface>();
}

void GLFactory::DestroyInterface(BearRHI::BearRHIInterface * a)
{
	bear_delete(static_cast<GLInterface*>(a));
}

BearRHI::BearRHIDefaultManager * GLFactory::CreateDefaultManager()
{
	return bear_new<GLDefaultManager>();
}

void GLFactory::DestroyDefaultManager(BearRHI::BearRHIDefaultManager * a)
{
	bear_delete(static_cast<GLDefaultManager*>(a));
}

BearRHI::BearRHIRenderTargetView * GLFactory::CreateRenderTargetView(bsize w, bsize h, BearGraphics::BearRenderTargetFormat format)
{
	return bear_new<GLRenderTergetView>(w,h,format);
}

void GLFactory::DestroyRenderTargetView(BearRHI::BearRHIRenderTargetView * a)
{
	bear_delete(static_cast<GLRenderTergetView*>(a));
}

BearRHI::BearRHIViewport * GLFactory::CreateViewport(void * win, bsize w, bsize h, bool fullscreen, bool vsync)
{
	return bear_new<GLViewport>(win,w,h,fullscreen,vsync);
}

void GLFactory::DestroyViewport(BearRHI::BearRHIViewport * a)
{
	bear_delete(static_cast<GLViewport*>(a));
}

BearRHI::BearRHITexture2D * GLFactory::CreateTexture2D(bsize w, bsize h, bsize mip, BearGraphics::BearTexturePixelFormat format, bool dynamic, void * data)
{
	return bear_new<GLTexture2D>(w,h,mip,format,dynamic,data);
}

void GLFactory::DestroyTexture2D(BearRHI::BearRHITexture2D * a)
{
	bear_delete(static_cast<GLTexture2D*>(a));
}

BearRHI::BearRHITexture2DArray * GLFactory::CreateTexture2DArray(bsize w, bsize h, bsize depth, bsize mip, BearGraphics::BearTexturePixelFormat format, void * data)
{
	return bear_new<GLTexture2DArray>(w, h, depth, mip, format,  data);
}

void GLFactory::DestroyTexture2DArray(BearRHI::BearRHITexture2DArray * a)
{
	bear_delete(static_cast<GLTexture2DArray*>(a));
}

BearRHI::BearRHIVertexBuffer * GLFactory::CreateVertexBuffer(void * data, bsize size, bool dynamic)
{
	return bear_new<GLVertexBuffer>( data,size,dynamic);
}

void GLFactory::DestroyVertexBuffer(BearRHI::BearRHIVertexBuffer * a)
{
	bear_delete(static_cast<GLVertexBuffer*>(a));
}

BearRHI::BearRHIIndexBuffer * GLFactory::CreateIndexBuffer(void * data, bsize size, bool dynamic)
{
	return bear_new<GLIndexBuffer>(data, size, dynamic);
}

void GLFactory::DestroyIndexBuffer(BearRHI::BearRHIIndexBuffer * a)
{
	bear_delete(static_cast<GLIndexBuffer*>(a));
}

BearRHI::BearRHIVertexShader * GLFactory::CreateVertexShader(void * data, bsize size)
{
	return bear_new<GLVertexShader>(data, size);;
}

void GLFactory::DestroyVertexShader(BearRHI::BearRHIVertexShader * a)
{
	bear_delete(static_cast<GLVertexShader*>(a));
}

BearRHI::BearRHIPixelShader * GLFactory::CreatePixelShader(void * data, bsize size)
{
	return bear_new<GLPixelShader>(data, size);;
}

void GLFactory::DestroyPixelShader(BearRHI::BearRHIPixelShader * a)
{
	bear_delete(static_cast<GLPixelShader*>(a));
}

BearRHI::BearRHIVertexShaderCompiler * GLFactory::CreateVertexShaderCompiler()
{
	return bear_new<GLVertexShaderCompiler>();;
}

void GLFactory::DestroyVertexShaderCompiler(BearRHI::BearRHIVertexShaderCompiler * a)
{
	bear_delete(static_cast<GLVertexShaderCompiler*>(a));
}

BearRHI::BearRHIPixelShaderCompiler * GLFactory::CreatePixelShaderCompiler()
{
	return bear_new<GLPixelShaderCompiler>();;
}

void GLFactory::DestroyPixelShaderCompiler(BearRHI::BearRHIPixelShaderCompiler * a)
{
	bear_delete(static_cast<GLPixelShaderCompiler*>(a));
}

BearRHI::BearRHIVertexState * GLFactory::CreateVertexState(const BearGraphics::BearVertexStateInitializer & initializer, void * data, bsize size)
{
	return bear_new<GLVertexState>(initializer,data,size);
}

void GLFactory::DestroyVertexState(BearRHI::BearRHIVertexState * a)
{
	bear_delete(static_cast<GLVertexState*>(a));
}

BearRHI::BearRHIDepthStencilView * GLFactory::CreateDepthStencilView(bsize w, bsize h, BearGraphics::BearDepthStencilFormat format)
{
	return bear_new<GLDepthStencilView>(w, h, format);
}

void GLFactory::DestroyDepthStencilView(BearRHI::BearRHIDepthStencilView * a)
{
	bear_delete(static_cast<GLDepthStencilView*>(a));
}

BearRHI::BearRHIDepthStencilState * GLFactory::CreateDepthStencilState(const BearGraphics::BearDepthStencilStateInitializer & initializer)
{
	return bear_new<GLDepthStencilState>(initializer);
}

void GLFactory::DestroyDepthStencilState(BearRHI::BearRHIDepthStencilState * a)
{
	bear_delete(static_cast<GLDepthStencilState*>(a));
}

BearRHI::BearRHISamplerState * GLFactory::CreateSamplerState(const BearGraphics::BearSamplerStateInitializer & initializer)
{
	return bear_new<GLSamplerState>(initializer);
}

void GLFactory::DestroySamplerState(BearRHI::BearRHISamplerState * a)
{
	bear_delete(static_cast<GLSamplerState*>(a));
}

BearRHI::BearRHIBlendState * GLFactory::CreateBlendState(const BearGraphics::BearBlendStateInitializer & initializer)
{
	return bear_new<GLBlendState>(initializer);
}

void GLFactory::DestroyBlendState(BearRHI::BearRHIBlendState * a)
{
	bear_delete(static_cast<GLBlendState*>(a));
}

BearRHI::BearRHIRasterizerState * GLFactory::CreateRasterizerState(const BearGraphics::BearRasterizerStateInitializer & initializer)
{
	return bear_new<GLRasterizerState>(initializer);
}

void GLFactory::DestroyRasterizerState(BearRHI::BearRHIRasterizerState * a)
{
	bear_delete(static_cast<GLRasterizerState*>(a));
}

BearRHI::BearRHIShaderConstants * GLFactory::CreateShaderConstants(const BearGraphics::BearShaderConstantsInitializer & initializer, bool dynamic)
{
	return bear_new<GLShaderConstants>(initializer, dynamic);
}

void GLFactory::DestroyShaderConstants(BearRHI::BearRHIShaderConstants * a)
{
	bear_delete(static_cast<GLShaderConstants*>(a));
}

GLFactory::~GLFactory()
{
}
