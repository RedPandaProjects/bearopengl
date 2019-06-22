#pragma once
class GLStats:public BearRHI::BearRHIStats
{
public:
	GLStats();
	virtual uint16 GetCountIndexBuffer() ;
	virtual uint16 GetCountVertexBuffer() ;

	virtual uint16 GetCountPixelShader() ;
	virtual uint16 GetCountPixelShaderCompiler();

	virtual uint16 GetCountVertexShader() ;
	virtual uint16 GetCountVertexShaderCompiler();

	virtual uint16 GetCountRenderTargetView();
	virtual uint16 GetCountViewPort();
	virtual uint16 GetCountDepthStencilView();

	virtual uint16 GetCountShaderConstants();

	virtual uint16 GetCountTexture1D() ;
	virtual uint16 GetCountTexture1DArray() ;
	virtual uint16 GetCountTexture2D() ;
	virtual uint16 GetCountTexture2DArray();
	virtual uint16 GetCountTexture3D();
	virtual uint16 GetCountTextureCubeMap();
	virtual uint16 GetCountTextureCubeMapArray();

	virtual uint16 GetCountVertexState();
	virtual uint16 GetCountBlendState();
	virtual uint16 GetCountSamplerState();
	virtual uint16 GetCountDepthStencilState();
	virtual uint16 GetCountRasterizerState();
	~GLStats();
};
struct GLBlendContainer
{
	GLBlendContainer() :
		Enable(false),
		AlphaBlendEnable(false),
		ColorBlendOperation(0xFFFFFF),
		ColorSourceBlendFactor(0xFFFFFF),
		ColorDestBlendFactor(0xFFFFFF),
		SeparateAlphaBlendEnable(false),
		AlphaBlendOperation(0xFFFFFF),
		AlphaSourceBlendFactor(0xFFFFFF),
		AlphaDestBlendFactor(0xFFFFFF),
		ColorWriteMaskR(false),
		ColorWriteMaskG(false),
		ColorWriteMaskB(false),
		ColorWriteMaskA(false)

	{}
	bool Enable;
	bool AlphaBlendEnable;
	GLenum ColorBlendOperation;
	GLenum ColorSourceBlendFactor;
	GLenum ColorDestBlendFactor;
	bool SeparateAlphaBlendEnable;
	GLenum AlphaBlendOperation;
	GLenum AlphaSourceBlendFactor;
	GLenum AlphaDestBlendFactor;
	bool ColorWriteMaskR;
	bool ColorWriteMaskG;
	bool ColorWriteMaskB;
	bool ColorWriteMaskA;
};
class GLBlendState :public BearRHI::BearRHIBlendState
{
public:
	GLBlendState(const BearGraphics::BearBlendStateInitializer&initializer);
	~GLBlendState();
	GLBlendContainer Container[8];
};

struct GLRasterizerContainer
{
	GLenum FillMode;
	GLenum CullMode;
	float DepthBias;
	float SlopeScaleDepthBias;

	GLRasterizerContainer()
		: FillMode(GL_FILL)
		, CullMode(GL_NONE)
		, DepthBias(0.0f)
		, SlopeScaleDepthBias(0.0f)
	{
	}
};
class GLRasterizerState :public BearRHI::BearRHIRasterizerState
{
public:
	GLRasterizerState(const BearGraphics::BearRasterizerStateInitializer&initializer);
	~GLRasterizerState();
	GLRasterizerContainer Container;

};

class GLDepthStencilContainer
{
public:
	bool bZEnable;
	bool bZWriteEnable;
	GLenum ZFunc;


	bool bStencilEnable;
	bool bTwoSidedStencilMode;
	GLenum StencilFunc;
	GLenum StencilFail;
	GLenum StencilZFail;
	GLenum StencilPass;
	GLenum CCWStencilFunc;
	GLenum CCWStencilFail;
	GLenum CCWStencilZFail;
	GLenum CCWStencilPass;
	uint32 StencilReadMask;
	uint32 StencilWriteMask;

	GLDepthStencilContainer()
		: bZEnable(false)
		, bZWriteEnable(false)
		, ZFunc(0xFFFFFFFF)
		, bStencilEnable(false)
		, bTwoSidedStencilMode(false)
		, StencilFunc(0xFFFFFFFF)
		, StencilFail(0xFFFFFFFF)
		, StencilZFail(0xFFFFFFFF)
		, StencilPass(0xFFFFFFFF)
		, CCWStencilFunc(0xFFFFFFFF)
		, CCWStencilFail(0xFFFFFFFF)
		, CCWStencilZFail(0xFFFFFFFF)
		, CCWStencilPass(0xFFFFFFFF)
		, StencilReadMask(0xFFFFFFFF)
		, StencilWriteMask(0xFFFFFFFF)
	{
	}
};
class GLDepthStencilState :public BearRHI::BearRHIDepthStencilState
{
public:
	GLDepthStencilState(const BearGraphics::BearDepthStencilStateInitializer&initializer);
	~GLDepthStencilState();
	GLDepthStencilContainer  Container;
};


class GLSamplerState :public BearRHI::BearRHISamplerState
{
public:
	GLSamplerState(const BearGraphics::BearSamplerStateInitializer&initializer);
	~GLSamplerState();
	GLuint Samplers;
};
class GLShaderConstants;
class GLVertexState :public BearRHI::BearRHIVertexState
{
public:
	GLVertexState(const BearGraphics::BearVertexStateInitializer&initializer, void*data, bsize size);
	~GLVertexState();
	void SetPixelShader(GLuint shader);
	void SetVertexShader(GLuint shader);
	void Update();
	void SetPixel(bsize slot,GLShaderConstants*constants);
	void SetVertex(bsize slot, GLShaderConstants*constants);
	GLuint GetProgram();
	GLuint Stride;
	GLuint GetPixelSlot(BearGraphics::BearConstantFormat Type, bsize Slot, bsize id);
	GLuint GetVertexSlot(BearGraphics::BearConstantFormat Type, bsize Slot, bsize id);
	GLuint GetPixelTextureSlot(bsize Slot);
	GLuint GetVertexTextureSlot(bsize Slot);
	BearGraphics::BearVertexStateElement Elements[16];
private:
	BearCore::BearMap<bsize, GLShaderConstants*> PixelMapConstants;
	BearCore::BearMap<bsize, GLShaderConstants*> VertexMapConstants;

	struct ShaderArray
	{
		ShaderArray() { BearCore::bear_fill(Array); }
		bool operator==(const ShaderArray&sh)const
		{
			return PixelShader == sh.PixelShader&&VertexShader == sh.VertexShader;
		}
		bool operator<(const ShaderArray&sh)const
		{
			if(PixelShader == sh.PixelShader)
				return VertexShader < sh.VertexShader;
			return PixelShader < sh.PixelShader;
		}
		union
		{
			struct
			{
				GLuint PixelShader;
				GLuint VertexShader;
			};
			GLuint Array[2];
		};
	} m_CurrentShaderArray;
	struct Item
	{
		Item() :Type(0), Slot(0),Id(0) {}
		Item(bsize Type, bsize Slot, bsize Id) :Type(Type), Slot(Slot), Id(Id) {}
		bsize Type;
		bsize Slot;
		bsize Id;
		bool operator<(const Item&it)const 
		{
			if (Type == it.Type)
			{
				if(Slot == it.Slot)
					return (Id < it.Id);
				return (Slot < it.Slot);
			}
			return (Type < it.Type);
		}
		bool operator==(const Item&it)const
		{
			if (Type == it.Type)
			{
				return (Slot == it.Slot) && Id == it.Id;
			}
			return false;
		}
	};
	struct ProgramContainer
	{
		BearCore::BearMap < Item, GLuint> MapItem;
		GLuint Program;
	};
	BearCore::BearMap<ShaderArray, ProgramContainer> m_MapGLProgram;


};

