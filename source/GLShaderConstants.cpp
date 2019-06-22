#include "GLPCH.h"
extern uint16 GCountShaderConstants;


GLShaderConstants::GLShaderConstants(const BearGraphics::BearShaderConstantsInitializer & initializer, bool dynamic):Constants(initializer.Constants),Size(0)
{
	GCountShaderConstants++;
	auto b = Constants.begin();
	auto e = Constants.end();
	while (b != e)
	{
		Size += GetSize(*b);
		b++;
	}
	Data = BearCore::bear_alloc<uint8>(Size);
}

GLShaderConstants::~GLShaderConstants()
{
	GCountShaderConstants--;
	BearCore::bear_free(Data);
}

void * GLShaderConstants::Lock()
{
	Update = true;
	return Data;
}

void GLShaderConstants::Unlock()
{
}

bsize GLShaderConstants::GetSize(BearGraphics::BearConstantFormat format)
{
	switch (format)
	{
	case BearGraphics::CF_R32_FLOAT:
		return sizeof(float) * 1;
		break;
	case BearGraphics::CF_R32G32_FLOAT:
		return sizeof(float) * 2;
		break;
	case BearGraphics::CF_R32G32B32_FLOAT:
		return sizeof(float) * 3;
		break;
	case BearGraphics::CF_R32G32B32A32_FLOAT:
		return sizeof(float) * 4;
		break;
	case BearGraphics::CF_R32_INT:
		return sizeof(int32);
	case BearGraphics::CF_MATRIX:
		return sizeof(float) * 4 * 4;
	default:
		return 0;
	}
}
