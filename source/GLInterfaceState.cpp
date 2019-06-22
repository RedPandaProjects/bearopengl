#include "GLPCH.h"

void GLInterface::UpdateRasterizerState(GLRasterizerContainer*RasterizerContainer)
{
	auto CurrentRasterizerContainer = &m_RasterizerContainer;
	if (Viewport)
	{
		CurrentRasterizerContainer = &static_cast<GLViewport*>(Viewport)->CurrentRasterizerContainer;
	}
	if (CurrentRasterizerContainer->FillMode != RasterizerContainer->FillMode)
	{
		CurrentRasterizerContainer->FillMode = RasterizerContainer->FillMode;
		DEBUGFATALERRORGL(glPolygonMode(GL_FRONT_AND_BACK, RasterizerContainer->FillMode));
	}
	

	if (CurrentRasterizerContainer->CullMode != RasterizerContainer->CullMode)
	{
		CurrentRasterizerContainer->CullMode = RasterizerContainer->CullMode;
		if (RasterizerContainer->CullMode != GL_NONE)
		{
			if (RasterizerContainer->CullMode == GL_NONE)
			{
				DEBUGFATALERRORGL(glEnable(GL_CULL_FACE));
			}
			DEBUGFATALERRORGL(glCullFace(RasterizerContainer->CullMode));
		}
		else
		{
			DEBUGFATALERRORGL(glDisable(GL_CULL_FACE));
		}
	}
	if (CurrentRasterizerContainer->DepthBias != RasterizerContainer->DepthBias ||
		CurrentRasterizerContainer->SlopeScaleDepthBias != RasterizerContainer->SlopeScaleDepthBias)
	{
		CurrentRasterizerContainer->DepthBias = RasterizerContainer->DepthBias;
		CurrentRasterizerContainer->SlopeScaleDepthBias = RasterizerContainer->SlopeScaleDepthBias;
		const float BiasScale = float((1 << 24) - 1);
		float DepthBias = RasterizerContainer->DepthBias * BiasScale;
		{
			if ((DepthBias == 0.0f) && (RasterizerContainer->SlopeScaleDepthBias == 0.0f))
			{
				DEBUGFATALERRORGL(glDisable(GL_POLYGON_OFFSET_FILL));
				DEBUGFATALERRORGL(glDisable(GL_POLYGON_OFFSET_LINE));
				DEBUGFATALERRORGL(glDisable(GL_POLYGON_OFFSET_POINT));
			}
			else
			{
				if (RasterizerContainer->DepthBias == 0.0f && RasterizerContainer->SlopeScaleDepthBias == 0.0f)
				{
					DEBUGFATALERRORGL(glEnable(GL_POLYGON_OFFSET_FILL));
					DEBUGFATALERRORGL(glEnable(GL_POLYGON_OFFSET_LINE));
					DEBUGFATALERRORGL(glEnable(GL_POLYGON_OFFSET_POINT));
				}
				DEBUGFATALERRORGL(glPolygonOffset(RasterizerContainer->SlopeScaleDepthBias, DepthBias));
			}

		}
	}

}

void GLInterface::UpdateDepthStencilState(GLDepthStencilContainer * DepthStencilContainer, uint32 StencilRef)
{
	auto CurrentDepthStencilContainer = &m_CurrentDepthStencilContainer;
	uint32 CurrentStencilRef = m_CurrentStencilRef;
	if (Viewport)
	{
		CurrentDepthStencilContainer = &static_cast<GLViewport*>(Viewport)->CurrentDepthStencilContainer;
		CurrentStencilRef = static_cast<GLViewport*>(Viewport)->CurrentStencilRef;
	}
	if (!DepthStencilContainer)return;
	if (CurrentDepthStencilContainer->bZEnable != DepthStencilContainer->bZEnable)
	{
		if (DepthStencilContainer->bZEnable)
			DEBUGFATALERRORGL(glEnable(GL_DEPTH_TEST))
		else
			DEBUGFATALERRORGL(glDisable(GL_DEPTH_TEST));
		CurrentDepthStencilContainer->bZEnable = DepthStencilContainer->bZEnable;
	}
	if (CurrentDepthStencilContainer->bZWriteEnable != DepthStencilContainer->bZWriteEnable)
	{
		DEBUGFATALERRORGL(glDepthMask(DepthStencilContainer->bZWriteEnable));
		CurrentDepthStencilContainer->bZWriteEnable = DepthStencilContainer->bZWriteEnable;
	}

	if (DepthStencilContainer->bZEnable)
	{
		if (CurrentDepthStencilContainer->ZFunc != DepthStencilContainer->ZFunc)
		{
			DEBUGFATALERRORGL(glDepthFunc(DepthStencilContainer->ZFunc));
			CurrentDepthStencilContainer->ZFunc = DepthStencilContainer->ZFunc;
		}
	}

	if (CurrentDepthStencilContainer->bStencilEnable != DepthStencilContainer->bStencilEnable)
	{
		if (DepthStencilContainer->bStencilEnable)
		{
			DEBUGFATALERRORGL(glEnable(GL_STENCIL_TEST));
		}
		else
		{
			DEBUGFATALERRORGL((GL_STENCIL_TEST));
		}
		CurrentDepthStencilContainer->bStencilEnable = DepthStencilContainer->bStencilEnable;
	}

	if (CurrentDepthStencilContainer->bTwoSidedStencilMode != DepthStencilContainer->bTwoSidedStencilMode)
	{

		CurrentDepthStencilContainer->StencilFunc = 0xFFFF;
		CurrentDepthStencilContainer->StencilFail = 0xFFFF;
		CurrentDepthStencilContainer->StencilZFail = 0xFFFF;
		CurrentDepthStencilContainer->StencilPass = 0xFFFF;
		CurrentDepthStencilContainer->CCWStencilFunc = 0xFFFF;
		CurrentDepthStencilContainer->CCWStencilFail = 0xFFFF;
		CurrentDepthStencilContainer->CCWStencilZFail = 0xFFFF;
		CurrentDepthStencilContainer->CCWStencilPass = 0xFFFF;
		CurrentDepthStencilContainer->StencilReadMask = 0xFFFF;

		CurrentDepthStencilContainer->bTwoSidedStencilMode = DepthStencilContainer->bTwoSidedStencilMode;
	}

	if (DepthStencilContainer->bStencilEnable)
	{
		if (DepthStencilContainer->bTwoSidedStencilMode)
		{
			if (DepthStencilContainer->StencilFunc != CurrentDepthStencilContainer->StencilFunc
				|| StencilRef != CurrentStencilRef
				|| CurrentDepthStencilContainer->StencilReadMask != DepthStencilContainer->StencilReadMask)
			{
				DEBUGFATALERRORGL(glStencilFuncSeparate(GL_BACK, DepthStencilContainer->StencilFunc, static_cast<GLint>(StencilRef), DepthStencilContainer->StencilReadMask));
				CurrentDepthStencilContainer->StencilFunc = DepthStencilContainer->StencilFunc;
			}

			if (CurrentDepthStencilContainer->StencilFail != DepthStencilContainer->StencilFail
				|| CurrentDepthStencilContainer->StencilZFail != DepthStencilContainer->StencilZFail
				|| CurrentDepthStencilContainer->StencilPass != DepthStencilContainer->StencilPass)
			{
				DEBUGFATALERRORGL(glStencilOpSeparate(GL_BACK, DepthStencilContainer->StencilFail, DepthStencilContainer->StencilZFail, DepthStencilContainer->StencilPass));
				CurrentDepthStencilContainer->StencilFail = DepthStencilContainer->StencilFail;
				CurrentDepthStencilContainer->StencilZFail = DepthStencilContainer->StencilZFail;
				CurrentDepthStencilContainer->StencilPass = DepthStencilContainer->StencilPass;
			}

			if (CurrentDepthStencilContainer->CCWStencilFunc != DepthStencilContainer->CCWStencilFunc
				|| StencilRef != CurrentStencilRef
				|| CurrentDepthStencilContainer->StencilReadMask != DepthStencilContainer->StencilReadMask)
			{
				DEBUGFATALERRORGL(glStencilFuncSeparate(GL_FRONT, DepthStencilContainer->CCWStencilFunc, static_cast<GLint>(StencilRef), DepthStencilContainer->StencilReadMask));
				CurrentDepthStencilContainer->CCWStencilFunc = DepthStencilContainer->CCWStencilFunc;
			}

			if (CurrentDepthStencilContainer->CCWStencilFail != DepthStencilContainer->CCWStencilFail
				|| CurrentDepthStencilContainer->CCWStencilZFail != DepthStencilContainer->CCWStencilZFail
				|| CurrentDepthStencilContainer->CCWStencilPass != DepthStencilContainer->CCWStencilPass)
			{
				DEBUGFATALERRORGL(glStencilOpSeparate(GL_FRONT, DepthStencilContainer->CCWStencilFail, DepthStencilContainer->CCWStencilZFail, DepthStencilContainer->CCWStencilPass));
				CurrentDepthStencilContainer->CCWStencilFail = DepthStencilContainer->CCWStencilFail;
				CurrentDepthStencilContainer->CCWStencilZFail = DepthStencilContainer->CCWStencilZFail;
				CurrentDepthStencilContainer->CCWStencilPass = DepthStencilContainer->CCWStencilPass;
			}

			CurrentDepthStencilContainer->StencilReadMask = DepthStencilContainer->StencilReadMask;
			StencilRef = CurrentStencilRef;
		}
		else
		{
			if (CurrentDepthStencilContainer->StencilFunc != DepthStencilContainer->StencilFunc
				|| StencilRef != CurrentStencilRef
				|| CurrentDepthStencilContainer->StencilReadMask != DepthStencilContainer->StencilReadMask)
			{
				DEBUGFATALERRORGL(glStencilFunc(DepthStencilContainer->StencilFunc, static_cast<GLint>(StencilRef), DepthStencilContainer->StencilReadMask));
				CurrentDepthStencilContainer->StencilFunc = DepthStencilContainer->StencilFunc;
				CurrentDepthStencilContainer->StencilReadMask = DepthStencilContainer->StencilReadMask;
				CurrentStencilRef = StencilRef;
			}

			if (CurrentDepthStencilContainer->StencilFail != DepthStencilContainer->StencilFail
				|| CurrentDepthStencilContainer->StencilZFail != DepthStencilContainer->StencilZFail
				|| CurrentDepthStencilContainer->StencilPass != DepthStencilContainer->StencilPass)
			{
				DEBUGFATALERRORGL(glStencilOp(DepthStencilContainer->StencilFail, DepthStencilContainer->StencilZFail, DepthStencilContainer->StencilPass));
				CurrentDepthStencilContainer->StencilFail = DepthStencilContainer->StencilFail;
				CurrentDepthStencilContainer->StencilZFail = DepthStencilContainer->StencilZFail;
				CurrentDepthStencilContainer->StencilPass = DepthStencilContainer->StencilPass;
			}
		}

		if (CurrentDepthStencilContainer->StencilWriteMask != DepthStencilContainer->StencilWriteMask)
		{
			DEBUGFATALERRORGL(glStencilMask(DepthStencilContainer->StencilWriteMask));
			CurrentDepthStencilContainer->StencilWriteMask = DepthStencilContainer->StencilWriteMask;
		}
	}
	DepthStencilContainer = 0;
}
void GLInterface::UpdateBlendState(GLBlendContainer * BlendContainer)
{
	auto CurrentBlendContainer = m_CurrentBlendContainer;
	if (Viewport)
	{
		CurrentBlendContainer = static_cast<GLViewport*>(Viewport)->CurrentBlendContainer;
	}
	for (bsize i = 0; i < 8; i++)
	{
		auto RenderTarget = &BlendContainer[i];
		auto CurrentRenderTarget = &CurrentBlendContainer[i];
		if (RenderTarget->AlphaBlendEnable != CurrentBlendContainer->AlphaBlendEnable)
		{
			CurrentBlendContainer->AlphaBlendEnable = RenderTarget->AlphaBlendEnable;
			if (RenderTarget->AlphaBlendEnable)
				DEBUGFATALERRORGL(glEnablei(GL_BLEND, static_cast<GLuint>(i)))
			else
				DEBUGFATALERRORGL(glDisablei(GL_BLEND, static_cast<GLuint>(i)));
		}
		if (BlendContainer[i].Enable)
		{
			bool Ñhange = false;
			if (RenderTarget->Enable != CurrentRenderTarget->Enable)
			{
				Ñhange = true;
				CurrentRenderTarget->Enable = RenderTarget->Enable;
			}
			if (RenderTarget->AlphaBlendEnable != CurrentRenderTarget->AlphaBlendEnable)
			{
				Ñhange = true;
				CurrentRenderTarget->AlphaBlendEnable = RenderTarget->AlphaBlendEnable;
			}
			if (RenderTarget->SeparateAlphaBlendEnable != CurrentRenderTarget->SeparateAlphaBlendEnable)
			{
				Ñhange = true;
				CurrentRenderTarget->SeparateAlphaBlendEnable = RenderTarget->SeparateAlphaBlendEnable;
			}

			if (RenderTarget->AlphaBlendEnable)
			{
				if (RenderTarget->SeparateAlphaBlendEnable)
				{
					if (RenderTarget->ColorSourceBlendFactor != CurrentRenderTarget->ColorSourceBlendFactor||
						RenderTarget->ColorDestBlendFactor != CurrentRenderTarget->ColorDestBlendFactor||
						RenderTarget->AlphaDestBlendFactor != CurrentRenderTarget->AlphaDestBlendFactor ||
						RenderTarget->AlphaSourceBlendFactor != CurrentRenderTarget->AlphaSourceBlendFactor ||
						
						Ñhange)
					{
						CurrentRenderTarget->ColorSourceBlendFactor = RenderTarget->ColorSourceBlendFactor;
						CurrentRenderTarget->ColorDestBlendFactor = RenderTarget->ColorDestBlendFactor;
						CurrentRenderTarget->AlphaDestBlendFactor = RenderTarget->AlphaDestBlendFactor;
						CurrentRenderTarget->AlphaSourceBlendFactor = RenderTarget->AlphaSourceBlendFactor;

						DEBUGFATALERRORGL(glBlendFuncSeparatei(static_cast<GLuint>(i), RenderTarget->ColorSourceBlendFactor, RenderTarget->ColorDestBlendFactor, RenderTarget->AlphaSourceBlendFactor, RenderTarget->AlphaDestBlendFactor));
					}
					if (RenderTarget->ColorBlendOperation != CurrentRenderTarget->ColorBlendOperation||
						RenderTarget->AlphaBlendOperation != CurrentRenderTarget->AlphaBlendOperation||
						Ñhange)
					{
						CurrentRenderTarget->ColorBlendOperation = RenderTarget->ColorBlendOperation;
						CurrentRenderTarget->AlphaBlendOperation = RenderTarget->AlphaBlendOperation;
						DEBUGFATALERRORGL(glBlendEquationSeparatei(static_cast<GLuint>(i), RenderTarget->ColorBlendOperation, RenderTarget->AlphaBlendOperation));

					}
				
				}
				else
				{
					if (RenderTarget->ColorSourceBlendFactor != CurrentRenderTarget->ColorSourceBlendFactor||
						RenderTarget->ColorDestBlendFactor != CurrentRenderTarget->ColorDestBlendFactor || 
						Ñhange)
					{
						CurrentRenderTarget->ColorSourceBlendFactor = RenderTarget->ColorSourceBlendFactor;
						CurrentRenderTarget->ColorDestBlendFactor = RenderTarget->ColorDestBlendFactor;
						DEBUGFATALERRORGL(glBlendFunci(static_cast<GLuint>(i), RenderTarget->ColorSourceBlendFactor, RenderTarget->ColorDestBlendFactor));

					}
					
					DEBUGFATALERRORGL(glBlendEquationi(static_cast<GLuint>(i), RenderTarget->ColorBlendOperation));
				}
			}
			else
			{
				if (RenderTarget->SeparateAlphaBlendEnable)
				{
					if (RenderTarget->ColorSourceBlendFactor != CurrentRenderTarget->ColorSourceBlendFactor ||
						RenderTarget->ColorDestBlendFactor != CurrentRenderTarget->ColorDestBlendFactor ||
						RenderTarget->AlphaDestBlendFactor != CurrentRenderTarget->AlphaDestBlendFactor ||
						RenderTarget->AlphaSourceBlendFactor != CurrentRenderTarget->AlphaSourceBlendFactor ||

						Ñhange)
					{
						CurrentRenderTarget->ColorSourceBlendFactor = RenderTarget->ColorSourceBlendFactor;
						CurrentRenderTarget->ColorDestBlendFactor = RenderTarget->ColorDestBlendFactor;
						CurrentRenderTarget->AlphaDestBlendFactor = RenderTarget->AlphaDestBlendFactor;
						CurrentRenderTarget->AlphaSourceBlendFactor = RenderTarget->AlphaSourceBlendFactor;

						DEBUGFATALERRORGL(glBlendFuncSeparate(RenderTarget->ColorSourceBlendFactor, RenderTarget->ColorDestBlendFactor, RenderTarget->AlphaSourceBlendFactor, RenderTarget->AlphaDestBlendFactor));
					}
					if (RenderTarget->ColorBlendOperation != CurrentRenderTarget->ColorBlendOperation ||
						RenderTarget->AlphaBlendOperation != CurrentRenderTarget->AlphaBlendOperation ||
						Ñhange)
					{
						CurrentRenderTarget->ColorBlendOperation = RenderTarget->ColorBlendOperation;
						CurrentRenderTarget->AlphaBlendOperation = RenderTarget->AlphaBlendOperation;
						DEBUGFATALERRORGL(glBlendEquationSeparate(RenderTarget->ColorBlendOperation, RenderTarget->AlphaBlendOperation));
					}
				}
				else
				{
					if (RenderTarget->ColorSourceBlendFactor != CurrentRenderTarget->ColorSourceBlendFactor ||
						RenderTarget->ColorDestBlendFactor != CurrentRenderTarget->ColorDestBlendFactor ||
						Ñhange)
					{
						CurrentRenderTarget->ColorSourceBlendFactor = RenderTarget->ColorSourceBlendFactor;
						CurrentRenderTarget->ColorDestBlendFactor = RenderTarget->ColorDestBlendFactor;
						DEBUGFATALERRORGL(glBlendFunc(RenderTarget->ColorSourceBlendFactor, RenderTarget->ColorDestBlendFactor));
					}
					if (RenderTarget->ColorBlendOperation != CurrentRenderTarget->ColorBlendOperation ||
						Ñhange)
					{
						CurrentRenderTarget->ColorBlendOperation = RenderTarget->ColorBlendOperation;
						DEBUGFATALERRORGL(glBlendEquation(RenderTarget->ColorBlendOperation));
					}
				}
			}
			if (RenderTarget->ColorWriteMaskR != CurrentRenderTarget->ColorWriteMaskR||
				RenderTarget->ColorWriteMaskG != CurrentRenderTarget->ColorWriteMaskG ||
				RenderTarget->ColorWriteMaskB != CurrentRenderTarget->ColorWriteMaskB ||
				RenderTarget->ColorWriteMaskA != CurrentRenderTarget->ColorWriteMaskA )
			{
				CurrentRenderTarget->ColorWriteMaskR = RenderTarget->ColorWriteMaskR;
				CurrentRenderTarget->ColorWriteMaskG = RenderTarget->ColorWriteMaskG;
				CurrentRenderTarget->ColorWriteMaskB = RenderTarget->ColorWriteMaskB;
				CurrentRenderTarget->ColorWriteMaskA = RenderTarget->ColorWriteMaskA;
				DEBUGFATALERRORGL(glColorMaski(static_cast<GLuint>(i), RenderTarget->ColorWriteMaskR, RenderTarget->ColorWriteMaskG, RenderTarget->ColorWriteMaskB, RenderTarget->ColorWriteMaskA));
			}
		}
	}
}