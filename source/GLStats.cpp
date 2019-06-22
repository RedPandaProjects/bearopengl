#include "GLPCH.h"
BearCore::BearMutex GMutexTexture;
BearCore::BearMutex GMutexViewport;
BearCore::BearMutex GRenderTargerMutex;
BearCore::BearMutex GShaderMutex;
BearCore::BearMutex GVertexStateMutex;
BearCore::BearMutex GSamplerStateMutex;
BearCore::BearMutex GBufferMutex;

uint16 GCountTexture = 0;
uint16 GCountViewport = 0;
uint16 GCountIndexBuffer = 0;
uint16 GCountVertexBuffer = 0;
uint16 GCountRenderTarger = 0;
uint16 GCountVertexShaderCompiler = 0;
uint16 GCountPixelShaderCompiler = 0;
uint16 GCountVertexShader = 0;
uint16 GCountPixelShader = 0;
uint16 GCountVertexState = 0;
uint16 GCountSamplerState = 0;
uint16 GCountBlendState = 0;
uint16 GCountDepthStencilView=0;
uint16 GCountShaderConstants=0;
uint16 GCountDepthStencilState=0;
uint16 GCountRasterizerState=0;
GLStats::GLStats()
{
}

uint16 GLStats::GetCountIndexBuffer()
{
	return GCountIndexBuffer;
}

uint16 GLStats::GetCountVertexBuffer()
{
	return GCountVertexBuffer;
}

uint16 GLStats::GetCountPixelShader()
{
	return GCountPixelShader;
}

uint16 GLStats::GetCountPixelShaderCompiler()
{
	return GCountPixelShaderCompiler;
}

uint16 GLStats::GetCountVertexShader()
{
	return GCountVertexShader;
}

uint16 GLStats::GetCountVertexShaderCompiler()
{
	return GCountVertexShaderCompiler;
}

uint16 GLStats::GetCountRenderTargetView()
{
	return GCountRenderTarger;
}

uint16 GLStats::GetCountViewPort()
{
	return GCountViewport;
}

uint16 GLStats::GetCountDepthStencilView()
{
	return GCountDepthStencilView;
}

uint16 GLStats::GetCountShaderConstants()
{
	return GCountShaderConstants;
}

uint16 GLStats::GetCountTexture1D()
{
	return uint16();
}

uint16 GLStats::GetCountTexture1DArray()
{
	return uint16();
}

uint16 GLStats::GetCountTexture2D()
{
	return GCountTexture;
}

uint16 GLStats::GetCountTexture2DArray()
{
	return uint16();
}

uint16 GLStats::GetCountTexture3D()
{
	return uint16();
}

uint16 GLStats::GetCountTextureCubeMap()
{
	return uint16();
}

uint16 GLStats::GetCountTextureCubeMapArray()
{
	return uint16();
}

uint16 GLStats::GetCountVertexState()
{
	return GCountVertexBuffer;
}

uint16 GLStats::GetCountBlendState()
{
	return GCountBlendState;
}

uint16 GLStats::GetCountSamplerState()
{
	return GCountSamplerState;
}

uint16 GLStats::GetCountDepthStencilState()
{
	return GCountDepthStencilState;
}

uint16 GLStats::GetCountRasterizerState()
{
	return GCountRasterizerState;
}

GLStats::~GLStats()
{
}


static GLenum TranslateBlendOp(BearGraphics::BearBlendOp BlendOp)
{
	switch (BlendOp)
	{
	case BearGraphics::BO_SUBTRACT: return GL_FUNC_SUBTRACT;
	case BearGraphics::BO_MIN: return GL_MIN;
	case BearGraphics::BO_MAX: return GL_MAX;
	case BearGraphics::BO_REV_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT;
	default: return GL_FUNC_ADD;
	};
}
static GLenum TranslateBlendFactor(BearGraphics::BearBlendFactor BlendFactor)
{
	switch (BlendFactor)
	{
	case BearGraphics::BF_ONE: return GL_ONE;
	case BearGraphics::BF_SRC_COLOR: return GL_SRC_COLOR;
	case BearGraphics::BF_INV_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
	case BearGraphics::BF_SRC_ALPHA: return GL_SRC_ALPHA;
	case BearGraphics::BF_INV_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
	case BearGraphics::BF_DEST_ALPHA: return GL_DST_ALPHA;
	case BearGraphics::BF_INV_DEST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
	case BearGraphics::BF_DEST_COLOR: return GL_DST_COLOR;
	case BearGraphics::BF_INV_DEST_COLOR: return GL_ONE_MINUS_DST_COLOR;
	case BearGraphics::BF_BLEND_FACTOR: return GL_CONSTANT_COLOR;
	case BearGraphics::BF_INV_BLEND_FACTOR: return GL_ONE_MINUS_CONSTANT_COLOR;
	default: return GL_ZERO;
	};
}

GLBlendState::GLBlendState(const BearGraphics::BearBlendStateInitializer & initializer)
{
	GCountBlendState++;
	BearCore::bear_fill(Container);
	for (bsize i = 0; i < 8&&initializer.RenderTarget[i].Enable; i++)
	{
		Container[i].Enable = true;
		Container[i].AlphaBlendEnable =
			initializer.RenderTarget[i].Color != BearGraphics::BO_ADD || initializer.RenderTarget[i].ColorDst != BearGraphics::BF_ZERO || initializer.RenderTarget[i].ColorSrc != BearGraphics::BF_ONE ||
			initializer.RenderTarget[i].Alpha != BearGraphics::BO_ADD || initializer.RenderTarget[i].AlphaDst != BearGraphics::BF_ZERO || initializer.RenderTarget[i].AlphaSrc != BearGraphics::BF_ONE;
		Container[i].ColorBlendOperation = TranslateBlendOp(initializer.RenderTarget[i].Color);
		Container[i].ColorSourceBlendFactor = TranslateBlendFactor(initializer.RenderTarget[i].ColorSrc);
		Container[i].ColorDestBlendFactor = TranslateBlendFactor(initializer.RenderTarget[i].ColorDst);
		Container[i].SeparateAlphaBlendEnable =
			initializer.RenderTarget[i].AlphaDst != initializer.RenderTarget[i].ColorDst ||
			initializer.RenderTarget[i].AlphaSrc != initializer.RenderTarget[i].ColorSrc;
		Container[i].AlphaBlendOperation = TranslateBlendOp(initializer.RenderTarget[i].Alpha);
		Container[i].AlphaSourceBlendFactor = TranslateBlendFactor(initializer.RenderTarget[i].AlphaSrc);
		Container[i].AlphaDestBlendFactor = TranslateBlendFactor(initializer.RenderTarget[i].AlphaDst);
		Container[i].ColorWriteMaskR =!!(initializer.RenderTarget[i].ColorWriteMask & BearGraphics::CWM_R);
		Container[i].ColorWriteMaskG =!! (initializer.RenderTarget[i].ColorWriteMask & BearGraphics::CWM_G);
		Container[i].ColorWriteMaskB = !!(initializer.RenderTarget[i].ColorWriteMask & BearGraphics::CWM_B);
		Container[i].ColorWriteMaskA = !!(initializer.RenderTarget[i].ColorWriteMask & BearGraphics::CWM_A);
	}
}

GLBlendState::~GLBlendState()
{
	GCountBlendState--;
}

GLRasterizerState::GLRasterizerState(const BearGraphics::BearRasterizerStateInitializer & initializer)
{
	GCountRasterizerState++;
	switch (initializer.CullMode)
	{
	case 	BearGraphics::RCM_FRONT:
		Container.CullMode = GL_FRONT;
		break;
	case 	BearGraphics::RCM_BACK:	
		Container.CullMode = GL_BACK;
		break;
	}
	switch (initializer.FillMode)
	{
	case BearGraphics::RFM_SOLID: 
		Container.FillMode = GL_FILL;
		break;
	case BearGraphics::RFM_WIREFRAME: 
		Container.FillMode = GL_LINE;
		break;
	}

	Container.DepthBias = initializer.DepthBias;
	Container.SlopeScaleDepthBias = initializer.SlopeScaleDepthBias;

}

GLRasterizerState::~GLRasterizerState()
{
	GCountRasterizerState--;
}



static GLenum TranslateCompareFunction(BearGraphics::BearCompareFunction CompareFunction)
{
	switch (CompareFunction)
	{
	case BearGraphics::CF_LESS: return GL_LESS;
	case BearGraphics::CF_LESSEQUAL: return GL_LEQUAL;
	case BearGraphics::CF_GREATER: return GL_GREATER;
	case BearGraphics::CF_GREATEREQUAL: return GL_GEQUAL;
	case BearGraphics::CF_EQUAL: return GL_EQUAL;
	case BearGraphics::CF_NOTEQUAL: return GL_NOTEQUAL;
	case BearGraphics::CF_NEVER: return GL_NEVER;
	default: return GL_ALWAYS;
	};
}
static GLenum TranslateStencilOp(BearGraphics::BearStencilOp StencilOp)
{
	switch (StencilOp)
	{
	case BearGraphics::SO_ZERO: return GL_ZERO;
	case BearGraphics::SO_REPLACE: return GL_REPLACE;
	case BearGraphics::SO_INCR_SAT: return GL_INCR;
	case BearGraphics::SO_DECR_SAT: return GL_DECR;
	case BearGraphics::SO_INVERT: return GL_INVERT;
	case BearGraphics::SO_INCR: return GL_INCR_WRAP;
	case BearGraphics::SO_DECR: return GL_DECR_WRAP;
	default: return GL_KEEP;
	};
}
GLDepthStencilState::GLDepthStencilState(const BearGraphics::BearDepthStencilStateInitializer & initializer)
{
	GCountDepthStencilState++;
	Container.bZEnable =   initializer.DepthEnable;
	Container.bZWriteEnable = initializer.DepthEnable;
	Container.ZFunc = TranslateCompareFunction(initializer.DepthTest);
	Container.bStencilEnable = initializer.StencillEnable || initializer.BackStencillEnable;

	Container.bTwoSidedStencilMode = initializer.BackStencillEnable;

	Container.StencilFunc = TranslateCompareFunction(initializer.FrontFace.StencilTest);
	Container.StencilFail = TranslateStencilOp(initializer.FrontFace.StencilFailOp);
	Container.StencilZFail = TranslateStencilOp(initializer.FrontFace.StencilDepthFailOp);
	Container.StencilPass = TranslateStencilOp(initializer.FrontFace.StencilPassOp);

	Container.CCWStencilFunc = TranslateCompareFunction(initializer.BackFace.StencilTest);
	Container.CCWStencilFail = TranslateStencilOp(initializer.BackFace.StencilFailOp);
	Container.CCWStencilZFail = TranslateStencilOp(initializer.BackFace.StencilDepthFailOp);
	Container.CCWStencilPass = TranslateStencilOp(initializer.BackFace.StencilPassOp);
	Container.StencilReadMask = initializer.StencilReadMask;
	Container.StencilWriteMask = initializer.StencilWriteMask;
}

GLDepthStencilState::~GLDepthStencilState()
{
	GCountDepthStencilState--;
}


static GLenum TranslateAddressMode(BearGraphics::BearSamplerAddressMode AddressMode)
{
	switch (AddressMode)
	{
	case BearGraphics::SAM_CLAMP: return GL_CLAMP_TO_EDGE;
	case BearGraphics::SAM_MIRROR: return GL_MIRRORED_REPEAT;
	case BearGraphics::SAM_BORDER: return GL_CLAMP_TO_BORDER;
	default: return GL_REPEAT;
	};
}
GLSamplerState::GLSamplerState(const BearGraphics::BearSamplerStateInitializer & initializer)
{
	BearCore::BearMutexLock lock(GSamplerStateMutex);
	GCountVertexState++;
	DEBUGFATALERRORGL(glGenSamplers(1, &Samplers));
	DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_WRAP_S, TranslateAddressMode(initializer.AddressU)));
	DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_WRAP_T, TranslateAddressMode(initializer.AddressV)));
	DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_WRAP_R, TranslateAddressMode(initializer.AddressW)));
	DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_LOD_BIAS,static_cast<GLint>( initializer.MipBias)));

	switch (initializer.Filter)
	{
	case	BearGraphics::SF_COMPARISON_MAG_MIP_POINT:
	case	BearGraphics::SF_MAG_MIP_POINT:
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
		break;
	case	BearGraphics::SF_COMPARISON_MAG_LINEAR_MIP_POINT:
	case	BearGraphics::SF_MAG_LINEAR_MIP_POINT:
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
		break;
	case	BearGraphics::SF_COMPARISON_MAG_MIP_LINEAR:
	case	BearGraphics::SF_MAG_MIP_LINEAR:
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		break;

	case	BearGraphics::SF_ANISOTROPIC:
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<GLint>(initializer.MaxAnisotropy > 0 ? initializer.MaxAnisotropy : 1)));
		break;
	case	BearGraphics::SF_COMPARISON_ANISOTROPIC:
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<GLint>(initializer.MaxAnisotropy > 0 ? initializer.MaxAnisotropy : 1)));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<GLint>(initializer.MaxAnisotropy > 0 ? initializer.MaxAnisotropy : 1)));
		break;
	default:
		break;
	}

	switch (initializer.Filter)
	{
	case	BearGraphics::SF_COMPARISON_ANISOTROPIC:
	case	BearGraphics::SF_COMPARISON_MAG_MIP_LINEAR:
	case	BearGraphics::SF_COMPARISON_MAG_LINEAR_MIP_POINT:
	case	BearGraphics::SF_COMPARISON_MAG_MIP_POINT:
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_COMPARE_FUNC, GL_LESS));
	default:
		DEBUGFATALERRORGL(glSamplerParameteri(Samplers, GL_TEXTURE_COMPARE_MODE, GL_NONE));
		break;
	}


}

GLSamplerState::~GLSamplerState()
{
	GCountVertexState--;
	DEBUGFATALERRORGL( glDeleteSamplers(1,&Samplers));
}
bsize GetSizeVertexFormat(BearGraphics::BearVertexFormat format)
{
	switch (format)
	{
	case BearGraphics::VF_R32G32B32A32_FLOAT:
		return 4 * 4;
	case BearGraphics::VF_R32G32B32_FLOAT:
		return 4 * 3;
	case BearGraphics::VF_R32G32_FLOAT:
		return 4 * 2;
	case BearGraphics::VF_R32_FLOAT:
		return 4 * 1;
	case BearGraphics::VF_R32_INT:
		return 4;
	case BearGraphics::VF_R8G8B8A8:
		return 4;
	case BearGraphics::VF_R8G8:
		return 2;
	case BearGraphics::VF_R8:
		return 1;
	default:
		BEAR_ASSERT(0);;
		return 0;
	}
}
GLVertexState::GLVertexState(const BearGraphics::BearVertexStateInitializer & initializer, void * data, bsize size):Stride(0)
{
	GCountVertexState++;
	for (bsize i = 0; i < 16; i++)
		Elements[i] = initializer.Elements[i];
	for (bsize i = 0; initializer.Elements[i].Type != BearGraphics::VF_NONE&&i < 16; i++)
	{
		Stride = BearCore::bear_max(Stride, static_cast<GLuint>(initializer.Elements[i].Offset) + static_cast<GLuint>(GetSizeVertexFormat(initializer.Elements[i].Type)));
	}
}

GLVertexState::~GLVertexState()
{
	BearCore::BearMutexLock lock(GVertexStateMutex);
	GCountVertexState--;
	if (this == GLInterface::VertexState)
	{
		GLInterface::VertexState = 0;
	}
	auto b = m_MapGLProgram.begin();
	auto e = m_MapGLProgram.end();
	while (b != e)
	{
		DEBUGFATALERRORGL(glDeleteProgram(b->second.Program));
		b++;
	}
}

void GLVertexState::SetPixelShader(GLuint shader)
{
	m_CurrentShaderArray.PixelShader = shader;
}

void GLVertexState::SetVertexShader(GLuint shader)
{
	m_CurrentShaderArray.VertexShader = shader;
}

void GLVertexState::Update()
{
	{
		auto b = PixelMapConstants.begin();
		auto e = PixelMapConstants.end();
		while (b != e)
		{
			if (!b->second->Update)
				return;
			b->second->Update = false;
			auto bc = b->second->Constants.begin();
			auto ec = b->second->Constants.end();
			
			bsize offset = 0, cnt_r = 0, cnt_rg = 0, cnt_rgb = 0, cnt_rgba = 0, cnt_ri = 0, cnt_mtx = 0;
			while (bc != ec)
			{
				switch (*bc)
				{
				case BearGraphics::CF_R32_FLOAT:
				{
					uint8* R = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform1f(GetPixelSlot(*bc, b->first, cnt_r), reinterpret_cast<float*>(R)[0]));
					cnt_r++;
					break;
				}
				case BearGraphics::CF_R32G32_FLOAT:
				{
					uint8* RG = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform2f(GetPixelSlot(*bc, b->first, cnt_rg), reinterpret_cast<float*>(RG)[0], reinterpret_cast<float*>(RG)[1]));
					cnt_rg++;
					break;
				}
				case BearGraphics::CF_R32G32B32_FLOAT:
#undef RGB
				{
					uint8* RGB = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform3f(GetPixelSlot(*bc, b->first, cnt_rgb), reinterpret_cast<float*>(RGB)[0], reinterpret_cast<float*>(RGB)[1], reinterpret_cast<float*>(RGB)[2]));
					cnt_rgb++;
					break;
				}
				case BearGraphics::CF_R32G32B32A32_FLOAT:
				{
					uint8* RGBA = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform4f(GetPixelSlot(*bc, b->first, cnt_rgba), reinterpret_cast<float*>(RGBA)[0], reinterpret_cast<float*>(RGBA)[1], reinterpret_cast<float*>(RGBA)[2], reinterpret_cast<float*>(RGBA)[3]));
					cnt_rgba++;
					break;
				}
				case BearGraphics::CF_R32_INT:
				{
					uint8* RI = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform1i(GetPixelSlot(*bc, b->first, cnt_ri), reinterpret_cast<int*>(RI)[0]));
					cnt_ri++;
					break;
				}
				case BearGraphics::CF_MATRIX:
				{
					uint8* Matrix = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniformMatrix4fv(GetPixelSlot(*bc, b->first, cnt_mtx), 1, GLboolean(GL_FALSE), reinterpret_cast<float*>(Matrix)));
					cnt_mtx++;
					break;
				}
				};
				offset += GLShaderConstants::GetSize(*bc);
				bc++;
			}
			b++;
		}
	}
	{
		auto b = VertexMapConstants.begin();
		auto e = VertexMapConstants.end();
		while (b != e)
		{
			if (!b->second->Update)
				return;
			b->second->Update = false;
			auto bc = b->second->Constants.begin();
			auto ec = b->second->Constants.end();
			bsize offset = 0, cnt_r = 0, cnt_rg = 0, cnt_rgb = 0, cnt_rgba = 0, cnt_ri = 0, cnt_mtx = 0;
			while (bc != ec)
			{
				switch (*bc)
				{
				case BearGraphics::CF_R32_FLOAT: 
				{
					uint8* R = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform1f(GetVertexSlot(*bc, b->first, cnt_r), reinterpret_cast<float*>(R)[0]));
					cnt_r++;
					break;
				}
				case BearGraphics::CF_R32G32_FLOAT:
				{
					uint8* RG = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform2f(GetVertexSlot(*bc, b->first, cnt_rg), reinterpret_cast<float*>(RG)[0], reinterpret_cast<float*>(RG)[1]));
					cnt_rg++;
					break;
				}
				case BearGraphics::CF_R32G32B32_FLOAT:
#undef RGB
				{
					uint8* RGB = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform3f(GetVertexSlot(*bc, b->first, cnt_rgb), reinterpret_cast<float*>(RGB)[0], reinterpret_cast<float*>(RGB)[1], reinterpret_cast<float*>(RGB)[2]));
					cnt_rgb++;
					break;
				}
				case BearGraphics::CF_R32G32B32A32_FLOAT:
				{
					uint8* RGBA = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform4f(GetVertexSlot(*bc, b->first, cnt_rgba), reinterpret_cast<float*>(RGBA)[0], reinterpret_cast<float*>(RGBA)[1], reinterpret_cast<float*>(RGBA)[2], reinterpret_cast<float*>(RGBA)[3]));
					cnt_rgba++;
					break;
				}
				case BearGraphics::CF_R32_INT:
				{
					uint8* RI = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniform1i(GetVertexSlot(*bc, b->first, cnt_ri), reinterpret_cast<int*>(RI)[0]));
					cnt_ri++;
					break;
				}
				case BearGraphics::CF_MATRIX:
				{
					uint8* Matrix = ((uint8*)b->second->Data + offset);
					DEBUGFATALERRORGL(glUniformMatrix4fv(GetVertexSlot(*bc, b->first, cnt_mtx), 1, GLboolean(GL_FALSE), reinterpret_cast<float*>(Matrix)));
					cnt_mtx++;
					break;
				}
				}
				offset += GLShaderConstants::GetSize(*bc);
				bc++;
			}
			b++;
		}
	}
}

void GLVertexState::SetPixel(bsize slot, GLShaderConstants * constants)
{
	auto item = PixelMapConstants.find(slot);
	constants->Update = true;
	if (item == PixelMapConstants.end())
	{
		PixelMapConstants.insert(slot, constants);
	}
	else
	{
		item->second = constants;
	}
}

void GLVertexState::SetVertex(bsize slot, GLShaderConstants * constants)
{
	auto item = VertexMapConstants.find(slot);
	constants->Update = true;
	if (item == VertexMapConstants.end())
	{
		VertexMapConstants.insert(slot, constants);
	}
	else
	{
		item->second = constants;
	}
}

GLuint GLVertexState::GetProgram()
{
	auto item = m_MapGLProgram.find(m_CurrentShaderArray);
	if(item==m_MapGLProgram.end())
	{
		GLuint Program;
		DEBUGFATALERRORGL(Program = glCreateProgram());
		DEBUGFATALERRORGL(glAttachShader(Program, m_CurrentShaderArray.PixelShader));
		DEBUGFATALERRORGL(glAttachShader(Program, m_CurrentShaderArray.VertexShader));
		for (bsize i = 0; i < 16 && Elements[i].Type != BearGraphics::VF_NONE; i++)
		{
			BearCore::BearStringAnsi256 Name;
			if (Elements[i].SemanticIndex)
				BearCore::BearString::Printf(Name, "%s%u", *Elements[i].Name, uint32(Elements[i].SemanticIndex));
			else
				BearCore::BearString::Copy(Name, *Elements[i].Name);
			DEBUGFATALERRORGL(glBindAttribLocation(Program, static_cast<GLuint>(i), *Elements[i].Name));
		}
		DEBUGFATALERRORGL(glLinkProgram(Program));
		GLint status;
		DEBUGFATALERRORGL(glGetProgramiv(Program, GL_LINK_STATUS, &status));
		if (status != 1)
		{
			GLint maxLength = 0;
			DEBUGFATALERRORGL(glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &maxLength));
			BearCore::BearVector<GLchar> infoLog; infoLog.resize(maxLength);
			DEBUGFATALERRORGL(glGetProgramInfoLog(Program, maxLength, &maxLength, &infoLog[0]));

			infoLog.push_back(0);
			BearCore::BearLog::Printf(TEXT("-----------OpenGL Shader program ошибка!----------------"));
			BearCore::BearLog::Printf(*BearCore::BearEncoding::ToCurrent((const char*)&infoLog[0]));
			BearCore::BearLog::Printf(TEXT("-------------------------------------------------"));
		}
		BEAR_ASSERT(status == 1);
		ProgramContainer container;
		container.Program = Program;
		m_MapGLProgram.insert(m_CurrentShaderArray, container);
		return Program;
	}
	return item->second.Program;
}

GLuint GLVertexState::GetPixelSlot(BearGraphics::BearConstantFormat Type, bsize Slot, bsize id)
{
	BearCore::BearMutexLock lock(GVertexStateMutex);
	auto item = m_MapGLProgram.find(m_CurrentShaderArray);
	if (item == m_MapGLProgram.end())
	{
		GetProgram();
		item = m_MapGLProgram.find(m_CurrentShaderArray);
	}
	auto item_shader = item->second.MapItem.find(Item(Type, Slot, id));
	if (item_shader == item->second.MapItem.end())
	{
		item = m_MapGLProgram.find(m_CurrentShaderArray);
		GLint location;
		BearCore::BearStringAnsi256 Name;
		const char*Type2Text = "";
		switch (Type)
		{
		case BearGraphics::CF_R32_FLOAT:
			Type2Text = "R";
			break;
		case BearGraphics::CF_R32G32_FLOAT:
			Type2Text = "RG";
			break;
		case BearGraphics::CF_R32G32B32_FLOAT:
			Type2Text = "RGB";
			break;
		case BearGraphics::CF_R32G32B32A32_FLOAT:
			Type2Text = "RGBA";
			break;
		case BearGraphics::CF_R32_INT:
			Type2Text = "RI";
			break;
		case BearGraphics::CF_MATRIX:
			Type2Text = "MATRIX";
			break;
		};
		BearCore::BearString::Printf(Name, "%s_%s_%u_%u", "PS", Type2Text, uint32(Slot),uint32(id));
		FATALERRORGL(location = glGetUniformLocation(GetProgram(), Name));
		item->second.MapItem.insert(Item(Type, Slot,id), location);
		return location;
	}
	return item_shader->second;
}

GLuint GLVertexState::GetVertexSlot(BearGraphics::BearConstantFormat Type, bsize Slot, bsize id)
{
	BearCore::BearMutexLock lock(GVertexStateMutex);
	auto item = m_MapGLProgram.find(m_CurrentShaderArray);
	if (item == m_MapGLProgram.end())
	{
		GetProgram();
		item = m_MapGLProgram.find(m_CurrentShaderArray);
	}
	auto item_shader = item->second.MapItem.find(Item(Type, Slot<<16||0xFFFF,id));
	if (item_shader == item->second.MapItem.end())
	{
		item = m_MapGLProgram.find(m_CurrentShaderArray);
		GLint location;
		BearCore::BearStringAnsi256 Name;
		const char*Type2Text = "";
		switch (Type)
		{
		case BearGraphics::CF_R32_FLOAT:
			Type2Text = "R";
			break;
		case BearGraphics::CF_R32G32_FLOAT:
			Type2Text = "RG";
			break;
		case BearGraphics::CF_R32G32B32_FLOAT:
			Type2Text = "RGB";
			break;
		case BearGraphics::CF_R32G32B32A32_FLOAT:
			Type2Text = "RGBA";
			break;
		case BearGraphics::CF_R32_INT:
			Type2Text = "RI";
			break;
		case BearGraphics::CF_MATRIX:
			Type2Text = "MATRIX";
			break;
		};
		BearCore::BearString::Printf(Name, "%s_%s_%u_%u","VS", Type2Text,uint32(Slot),uint32(id));
		FATALERRORGL(location = glGetUniformLocation(GetProgram(), Name));
		item->second.MapItem.insert(Item(Type, Slot << 16 || 0xFFFF,id), location);
		return location;
	}
	return item_shader->second;
}

GLuint GLVertexState::GetPixelTextureSlot(bsize Slot)
{
	BearCore::BearMutexLock lock(GVertexStateMutex);
	auto item = m_MapGLProgram.find(m_CurrentShaderArray);
	if (item == m_MapGLProgram.end())
	{

		GetProgram();
		item = m_MapGLProgram.find(m_CurrentShaderArray);
	}
	auto item_shader = item->second.MapItem.find(Item(0xFFFF + 0xFFFF, Slot,1));
	if (item_shader == item->second.MapItem.end())
	{
		GLint location;
		BearCore::BearStringAnsi256 Name;
		BearCore::BearString::Printf(Name, "%s_%s%u", "PS", "TEXTURE", uint32(Slot));
		FATALERRORGL(location = glGetUniformLocation(GetProgram(), Name));
		item->second.MapItem.insert(Item(0xFFFF + 0xFFFF, Slot,1), location);
		return location;
	}
	return item_shader->second;
}

GLuint GLVertexState::GetVertexTextureSlot(bsize Slot)
{
	auto item = m_MapGLProgram.find(m_CurrentShaderArray);
	if (item == m_MapGLProgram.end())
	{
		GetProgram();
		item = m_MapGLProgram.find(m_CurrentShaderArray);
	}
	auto item_shader = item->second.MapItem.find(Item(0xFFFF+0xFFFF, Slot,0));
	if (item_shader == item->second.MapItem.end())
	{
		item = m_MapGLProgram.find(m_CurrentShaderArray);
		GLint location;
		BearCore::BearStringAnsi256 Name;
		BearCore::BearString::Printf(Name, "%s_%s%u", "VS", "TEXTURE", uint32(Slot));
		FATALERRORGL(location = glGetUniformLocation(GetProgram(), Name));
		item->second.MapItem.insert(Item(0xFFFF + 0xFFFF, Slot,0), location);
		return location;
	}
	return item_shader->second;
}
