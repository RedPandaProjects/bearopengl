#include "GLPCH.h"
GLuint GlobalRenderTarget;
extern BearCore::BearMutex GMutexViewport;
extern BearCore::BearMutex GRenderTargerMutex;

extern BearCore::BearMutex GVertexStateMutex;
GLVertexState *GLInterface::VertexState=0;

extern BearCore::BearMutex GBufferMutex;

extern BearCore::BearMutex GMutexTexture;
extern BearCore::BearMutex GSamplerStateMutex;

GLInterface::GLInterface() :Viewport(0), VertexBuffer(0), IndexBuffer(0), m_UpdateRenderTarget(true), DepthStencilView(0), m_viewport(1,1)
{
	InitializePlatform();
	DEBUGFATALERRORGL(glGenFramebuffers(1, &GlobalRenderTarget));
	BearCore::bear_fill(RenderTargetViewArray, 8, 0);
	DEBUGFATALERRORGL(glGenVertexArrays(1, &VertexArray));
	DEBUGFATALERRORGL(glBindVertexArray(VertexArray));
	DEBUGFATALERRORGL(glActiveTexture(GL_TEXTURE31));
	RasterizerState = 0;
	DepthStencilState = 0;
	BlendState = 0;
	DEBUGFATALERRORGL(glClearDepth(1.f));
	DEBUGFATALERRORGL(glFrontFace(GL_CW));
	DEBUGFATALERRORGL(glEnable(GL_CULL_FACE));
	DEBUGFATALERRORGL(glCullFace(GL_BACK));
	DEBUGFATALERRORGL(glDisable(GL_DEPTH_TEST));
	DEBUGFATALERRORGL(glDepthMask(GL_FALSE));
	//DEBUGFATALERRORGL(glEnable(GL_TEXTURE_2D));
}

void GLInterface::Clear()
{
}

void GLInterface::AttachViewport( BearRHI::BearRHIViewport * render_target)
{
	Viewport = render_target; m_UpdateRenderTarget = true;
}

void GLInterface::AttachRenderTargetView(uint32 id, BearRHI::BearRHIRenderTargetView * render_target)
{
	BearCore::BearMutexLock lock(GMutexViewport);
	RenderTargetViewArray[id] = render_target; m_UpdateRenderTarget = true;
}

void GLInterface::AttachDepthStencilView(BearRHI::BearRHIDepthStencilView * depthStencill)
{
	DepthStencilView = depthStencill;
	m_UpdateRenderTarget = true;
}

void GLInterface::DetachRenderTargetView(uint32 id)
{
	BearCore::BearMutexLock lock(GRenderTargerMutex);
	RenderTargetViewArray[id] = 0; m_UpdateRenderTarget = true;
}

void GLInterface::DetachDepthStencilView()
{
	DepthStencilView = 0;
	m_UpdateRenderTarget = true;
}

void GLInterface::DetachViewport()
{
	m_UpdateRenderTarget = true;
	Viewport = 0;
}

void GLInterface::SetViewport(float x, float y, float width, float height, float minDepth, float maxDepth)
{
	DEBUGFATALERRORGL(glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height)));
	DEBUGFATALERRORGL(glDepthRangef(minDepth, maxDepth));
	m_viewport.set(width, height);
}

void GLInterface::SetScissor(bool  enable, float x, float y, float x1, float y1)
{
	static bool Enable = false;
	if (Enable!=enable)
	{
		Enable = enable;
		if (enable)
		{
			DEBUGFATALERRORGL(glEnable(GL_SCISSOR_TEST));
		}
		else
		{
			DEBUGFATALERRORGL(glDisable(GL_SCISSOR_TEST));
		}
	}
	if (Enable)
	{
		/*if (m_viewport.x < x1 + x)
		{
			x1 = m_viewport.x - x;
		}
		if (m_viewport.y < y1 +y)
		{
			y1 = m_viewport.y - y;
		}*/
		DEBUGFATALERRORGL(glScissor(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(x1)+ static_cast<GLint>(x), static_cast<GLsizei>(y1)+ static_cast<GLint>(y1)));
	}
}

void GLInterface::SetPixelShader(BearRHI::BearRHIPixelShader * shader)
{
	if (VertexState == 0)return;
	VertexState->SetPixelShader(static_cast<GLPixelShader*>(shader)->Shader);
}

void GLInterface::SetVertexShader(BearRHI::BearRHIVertexShader * shader)
{
	if (VertexState == 0)return;
	VertexState->SetVertexShader(static_cast<GLVertexShader*>(shader)->Shader);
}

void GLInterface::SetIndexBuffer(BearRHI::BearRHIIndexBuffer * buffer)
{
	IndexBuffer = static_cast<GLIndexBuffer*>(buffer)->Buffer;
}

void GLInterface::SetVertexBuffer(BearRHI::BearRHIVertexBuffer * buffer)
{
	VertexBuffer = static_cast<GLVertexBuffer*>(buffer)->Buffer;
}

void GLInterface::SetVertexState(BearRHI::BearRHIVertexState * buffer)
{
	VertexState = static_cast<GLVertexState*>(buffer);
}

void GLInterface::SetBlendState(BearRHI::BearRHIBlendState * State, const BearCore::BearColor & color)
{
	BlendState = static_cast<GLBlendState*>(State);
}

void GLInterface::SetDepthStencilState(BearRHI::BearRHIDepthStencilState * State, uint32 StenciRef)
{
	DepthStencilState_StencilRef = StenciRef;
	DepthStencilState = static_cast<GLDepthStencilState*>(State);
}

void GLInterface::SetRasterizerState(BearRHI::BearRHIRasterizerState * State)
{
	RasterizerState = static_cast<GLRasterizerState*>(State);
}

void GLInterface::SetVertexShaderConstants(bsize slot, BearRHI::BearRHIShaderConstants * constants)
{
	if (VertexState == 0)return;
	BearCore::BearMutexLock lock_vertex_state(GVertexStateMutex);
	VertexState->SetVertex(slot, static_cast<GLShaderConstants*>(constants));
}

void GLInterface::SetVertexShaderResource(bsize slot, BearRHI::BearRHITexture2D * texture2d, BearRHI::BearRHISamplerState * sampler)
{
	if (VertexState == 0)return;
	BearCore::BearMutexLock lock(GMutexTexture);
	BearCore::BearMutexLock lock_sampler(GSamplerStateMutex);

	auto Texture = static_cast<GLTexture2D*>(texture2d);
	auto Sampler = static_cast<GLSamplerState*>(sampler);
	DEBUGFATALERRORGL(glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + slot)));
	DEBUGFATALERRORGL(glBindTexture(GL_TEXTURE_2D, Texture->Texture));
	DEBUGFATALERRORGL(glBindSampler(static_cast<GLuint>(slot), Sampler->Samplers));
	DEBUGFATALERRORGL(glUniform1i(VertexState->GetVertexTextureSlot(slot), static_cast<GLint>(slot)));
	DEBUGFATALERRORGL(glActiveTexture(GL_TEXTURE31));
}

void GLInterface::SetPixelShaderConstants(bsize slot, BearRHI::BearRHIShaderConstants * constants)
{
	if (VertexState == 0)return;
	BearCore::BearMutexLock lock_vertex_state(GVertexStateMutex);
	VertexState->SetPixel(slot, static_cast<GLShaderConstants*>(constants));
}

void GLInterface::SetPixelShaderResource(bsize slot, BearRHI::BearRHITexture2D * texture2d, BearRHI::BearRHISamplerState * sampler)
{
	if (VertexState == 0)return;
	BearCore::BearMutexLock lock(GMutexTexture);
	BearCore::BearMutexLock lock_sampler(GSamplerStateMutex);
	BearCore::BearMutexLock lock_vertex_state(GVertexStateMutex);
	DEBUGFATALERRORGL(glUseProgram(VertexState->GetProgram()));
	auto Texture = static_cast<GLTexture2D*>(texture2d);
	auto Sampler = static_cast<GLSamplerState*>(sampler);
	DEBUGFATALERRORGL(glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + slot)));
	DEBUGFATALERRORGL(glBindTexture(GL_TEXTURE_2D, Texture->Texture));
	DEBUGFATALERRORGL(glBindSampler(static_cast<GLuint>(slot), Sampler->Samplers));
	DEBUGFATALERRORGL(glUniform1i(VertexState->GetPixelTextureSlot(slot), static_cast<GLint>(slot)));
	DEBUGFATALERRORGL(glActiveTexture(GL_TEXTURE31));

}
GLint TranslateModeDraw(BearGraphics::BearDrawType mode)
{
	switch (mode)
	{
	case BearGraphics::DT_POINT:
		return GL_POINTS;
	case BearGraphics::DT_LINE:
		return GL_LINES;
	case BearGraphics::DT_TRIANGLE:
		return GL_TRIANGLES;
	default:
		BEAR_ASSERT(0);
		return GL_POINTS;
	}
//	return GL_NONE;
}

void GLInterface::DrawIndexed(bsize size, bsize possition, BearGraphics::BearDrawType mode)
{
	BearCore::BearMutexLock lock(GVertexStateMutex);
	BearCore::BearMutexLock lock_buffer(GBufferMutex);
	if (VertexState == 0 || VertexBuffer == 0 || IndexBuffer == 0)return;
	GLenum RenderTargetArray[8];
	GRenderTargerMutex.Lock();
	if (m_UpdateRenderTarget)
	{
		m_UpdateRenderTarget = false;

		if (Viewport)
		{
			GMutexViewport.Lock();
			BEAR_ASSERT(dynamic_cast<GLViewport*>(Viewport));
			static_cast<GLViewport*>(Viewport)->MakeCurrent();
			DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			//RenderTargetArray[0] = GL_COLOR_BACK;
			DEBUGFATALERRORGL(glDrawBuffer(GL_BACK));
		}
		else
		{
			for (bsize i = 0; i < 8; i++)
			{
				DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, GlobalRenderTarget));
				if (RenderTargetViewArray[i])
				{
					BEAR_ASSERT(dynamic_cast<GLRenderTergetView*>(RenderTargetViewArray[i]));
					RenderTargetArray[i] = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i);
					DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i), static_cast<GLRenderTergetView*>(RenderTargetViewArray[i])->Texture->Texture, 0));
				}
				else
				{
					RenderTargetArray[i] = GL_NONE;
				}
				DEBUGFATALERRORGL(glDrawBuffers(8, RenderTargetArray));
			}
			if (DepthStencilView)
			{
				if (static_cast<GLDepthStencilView*>(DepthStencilView)->IsStencil())
				{
					DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, static_cast<GLDepthStencilView*>(DepthStencilView)->Texture->Texture, 0));
				}
				else
				{
					DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, static_cast<GLDepthStencilView*>(DepthStencilView)->Texture->Texture, 0));

				}
			}
			else
			{
				DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0));

			}

		}

	}
	else
	{
		if (Viewport)
		{
			BEAR_ASSERT(dynamic_cast<GLViewport*>(Viewport));
			static_cast<GLViewport*>(Viewport)->MakeCurrent();
		}
	}
	if (RasterizerState)UpdateRasterizerState(&RasterizerState->Container);
	if (BlendState)UpdateBlendState(BlendState->Container);
	if (DepthStencilState)UpdateDepthStencilState(&DepthStencilState->Container, DepthStencilState_StencilRef);

	DEBUGFATALERRORGL(glUseProgram(VertexState->GetProgram()));
	VertexState->Update();
	DEBUGFATALERRORGL(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer));
	for (bsize i = 0; VertexState->Elements[i].Type != BearGraphics::VF_NONE&&i < 16; i++)
	{
		DEBUGFATALERRORGL(glEnableVertexAttribArray(static_cast<GLuint>(i)));
		switch (VertexState->Elements[i].Type)
		{
		case	BearGraphics::VF_R32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 1, GL_FLOAT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32G32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32G32B32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 3, GL_FLOAT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32G32B32A32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 4, GL_FLOAT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32_INT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 1, GL_INT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R8:
			DEBUGFATALERRORGL(glVertexAttribIPointer(static_cast<GLuint>(i), 1, GL_UNSIGNED_BYTE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R8G8:
			DEBUGFATALERRORGL(glVertexAttribIPointer(static_cast<GLuint>(i), 2, GL_UNSIGNED_BYTE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R8G8B8A8:
			DEBUGFATALERRORGL(glVertexAttribIPointer(static_cast<GLuint>(i), 4, GL_UNSIGNED_BYTE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));

			break;
		}
	}

	DEBUGFATALERRORGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer));
	DEBUGFATALERRORGL(glDrawElements(TranslateModeDraw(mode), static_cast<GLsizei>(size), GL_UNSIGNED_INT, (uint8*)0 + 4 * possition));
	for (bsize i = 0; VertexState->Elements[i].Type != BearGraphics::VF_NONE&&i < 16; i++)
	{
		DEBUGFATALERRORGL(glDisableVertexAttribArray(static_cast<GLuint>(i)));
	}
	if (Viewport)
	{
		GMutexViewport.Unlock();
	}
	GRenderTargerMutex.Unlock();
}

void GLInterface::Draw(bsize size, bsize possition, BearGraphics::BearDrawType mode)
{
	BearCore::BearMutexLock lock(GVertexStateMutex);
	BearCore::BearMutexLock lock_buffer(GBufferMutex);
	if (VertexState == 0|| VertexBuffer==0|| IndexBuffer==0)return;
	GLenum RenderTargetArray[8];
	GRenderTargerMutex.Lock();
	if (m_UpdateRenderTarget)
	{
		m_UpdateRenderTarget = false;

		if (Viewport)
		{
			GMutexViewport.Lock();
			BEAR_ASSERT(dynamic_cast<GLViewport*>(Viewport));
			static_cast<GLViewport*>(Viewport)->MakeCurrent();
			DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			//RenderTargetArray[0] = GL_COLOR_BACK;
			DEBUGFATALERRORGL(glDrawBuffer(GL_BACK));
		}
		else
		{
			for (bsize i = 0; i < 8; i++)
			{
				DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, GlobalRenderTarget));
				if (RenderTargetViewArray[i])
				{
					BEAR_ASSERT(dynamic_cast<GLRenderTergetView*>(RenderTargetViewArray[i]));
					RenderTargetArray[i] = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i);
					DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE_2D, GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i), static_cast<GLRenderTergetView*>(RenderTargetViewArray[i])->Texture->Texture, 0));
				}
				else
				{
					RenderTargetArray[i] = GL_NONE;
				}
				DEBUGFATALERRORGL(glDrawBuffers(8, RenderTargetArray));
			}
			if (DepthStencilView)
			{
				if (static_cast<GLDepthStencilView*>(DepthStencilView)->IsStencil())
				{
					DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, static_cast<GLDepthStencilView*>(DepthStencilView)->Texture->Texture, 0));
				}
				else
				{
					DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, static_cast<GLDepthStencilView*>(DepthStencilView)->Texture->Texture, 0));

				}
			}
			else
			{
				DEBUGFATALERRORGL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0));

			}

		}

	}
	else
	{
		if (Viewport)
		{
			BEAR_ASSERT(dynamic_cast<GLViewport*>(Viewport));
			static_cast<GLViewport*>(Viewport)->MakeCurrent();
		}
	}
	if (RasterizerState)UpdateRasterizerState(&RasterizerState->Container);
	if (BlendState)UpdateBlendState(BlendState->Container);
	if(DepthStencilState)UpdateDepthStencilState(&DepthStencilState->Container,DepthStencilState_StencilRef);

	DEBUGFATALERRORGL(glUseProgram(VertexState->GetProgram()));
	VertexState->Update();
	DEBUGFATALERRORGL(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer));
	for (bsize i = 0; VertexState->Elements[i].Type!=BearGraphics::VF_NONE&&i<16; i++) 
	{
		DEBUGFATALERRORGL(glEnableVertexAttribArray(static_cast<GLuint>(i)));
		switch (VertexState->Elements[i].Type)
		{
		case	BearGraphics::VF_R32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i),1,GL_FLOAT,GL_FALSE,static_cast<GLuint>(VertexState->Stride),(uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32G32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32G32B32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 3, GL_FLOAT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32G32B32A32_FLOAT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 4, GL_FLOAT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R32_INT:
			DEBUGFATALERRORGL(glVertexAttribPointer(static_cast<GLuint>(i), 1, GL_INT, GL_FALSE, static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R8:
			DEBUGFATALERRORGL(glVertexAttribIPointer(static_cast<GLuint>(i), 1, GL_UNSIGNED_BYTE,  static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R8G8:
			DEBUGFATALERRORGL(glVertexAttribIPointer(static_cast<GLuint>(i), 2, GL_UNSIGNED_BYTE,  static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));
			break;
		case	BearGraphics::VF_R8G8B8A8:
			DEBUGFATALERRORGL(glVertexAttribIPointer(static_cast<GLuint>(i), 4, GL_UNSIGNED_BYTE,  static_cast<GLuint>(VertexState->Stride), (uint8*)0 + VertexState->Elements[i].Offset));

			break;
		}
	}
	
	DEBUGFATALERRORGL(glDrawArrays(TranslateModeDraw(mode), static_cast<GLint>(possition), static_cast<GLsizei>(size)));
	for (bsize i = 0; VertexState->Elements[i].Type != BearGraphics::VF_NONE&&i < 16; i++)
	{
		DEBUGFATALERRORGL(glDisableVertexAttribArray(static_cast<GLuint>(i)));
	}
	if (Viewport)
	{
		GMutexViewport.Unlock();
	}
	GRenderTargerMutex.Unlock();
}

GLInterface::~GLInterface()
{
	DEBUGFATALERRORGL(glDeleteFramebuffers(1, &GlobalRenderTarget));
	DEBUGFATALERRORGL(glBindVertexArray(GL_NONE));
	DEBUGFATALERRORGL(glDeleteVertexArrays(1, &VertexArray));
	DestroyPlatform();
}

GLint GLInterface::TranslatePixelFormat(BearGraphics::BearTexturePixelFormat px)
{
	switch (px)
	{
	case BearGraphics::TPF_R8:
		return GL_RED;
		break;
	case BearGraphics::TPF_R8G8:
		return GL_RG;
		break;
	case BearGraphics::TPF_R8G8B8:
		return GL_RGB;
		break;
	case BearGraphics::TPF_R8G8B8A8:
		return GL_RGBA;
		break;
	case BearGraphics::TPF_R32F:
		return GL_RED;
		break;
	case BearGraphics::TPF_R32G32F:
		return GL_RG;
		break;
	case BearGraphics::TPF_R32G32B32F:
		return GL_RGB;
		break;
	case BearGraphics::TPF_R32G32B32A32F:
		return GL_RGBA;
		break;
	case BearGraphics::TPF_BC2:
		return		GL_RGBA;
	case BearGraphics::TPF_BC3:
		return		GL_RGBA;
	case BearGraphics::TPF_BC1:
		return 		 GL_RGB;
	case BearGraphics::TPF_BC1a:
		return 		 GL_RGBA;
	case BearGraphics::TPF_BC4:
		return GL_RED;
	case BearGraphics::TPF_BC5:
		return GL_RG;
	case BearGraphics::TPF_BC6:
		return GL_RGBA;
	case BearGraphics::TPF_BC7:
		return GL_RGBA;
	default:
		break;
	}
	return GL_NONE;
}

GLint GLInterface::TranslatePixelType(BearGraphics::BearTexturePixelFormat px)
{
	switch (px)
	{
	case BearGraphics::TPF_R8:
	case BearGraphics::TPF_R8G8:
	case BearGraphics::TPF_R8G8B8:
	case BearGraphics::TPF_R8G8B8A8:
		return GL_UNSIGNED_BYTE;
	case BearGraphics::TPF_R32G32B32A32F:
	case BearGraphics::TPF_R32G32B32F:
	case BearGraphics::TPF_R32G32F:
	case BearGraphics::TPF_R32F:
		return GL_FLOAT;
	case BearGraphics::TPF_BC1:
	case BearGraphics::TPF_BC1a:
	case BearGraphics::TPF_BC2:
	case BearGraphics::TPF_BC3:
	case BearGraphics::TPF_BC4:
	case BearGraphics::TPF_BC5:
		return GL_UNSIGNED_BYTE;
	case BearGraphics::TPF_BC6:
		return GL_HALF_FLOAT;
	case BearGraphics::TPF_BC7:
		return GL_UNSIGNED_BYTE;
	default:
		break;
	}
	return GL_NONE;
}
GLint GLInterface::TranslatePixelFormatI(BearGraphics::BearTexturePixelFormat px)
{

	switch (px)
	{
	case BearGraphics::TPF_R8:
		return GL_R8;
		break;
	case BearGraphics::TPF_R8G8:
		return GL_RG8;
		break;
	case BearGraphics::TPF_R8G8B8:
		return GL_RGB8;
		break;
	case BearGraphics::TPF_R8G8B8A8:
		return GL_RGBA8;
		break;
	case BearGraphics::TPF_R32F:
		return GL_R32F;
		break;
	case BearGraphics::TPF_R32G32F:
		return GL_RG32F;
		break;
	case BearGraphics::TPF_R32G32B32F:
		return GL_RGB32F;
		break;
	case BearGraphics::TPF_R32G32B32A32F:
		return GL_RGBA32F;
		break;
	case BearGraphics::TPF_BC2:
		return		GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case BearGraphics::TPF_BC3:
		return		GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case BearGraphics::TPF_BC1:
		return 		 GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
	case BearGraphics::TPF_BC1a:
		return 		 GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case BearGraphics::TPF_BC4:
		return GL_COMPRESSED_RED_RGTC1;
	case BearGraphics::TPF_BC5:
		return GL_COMPRESSED_RG_RGTC2;
	case BearGraphics::TPF_BC6:
		return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
	case BearGraphics::TPF_BC7:
		return GL_COMPRESSED_RGBA_BPTC_UNORM;
	}
	return GL_NONE;
}