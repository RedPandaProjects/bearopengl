#include "GLPCH.h"
GLFactory *Factory;
GLStats Stats;
void RHIInitialize()
{
	
	if (GLInterface::IsSupport())
	{
		Factory = BearCore::bear_new<GLFactory>();
		RHIFactoty = Factory;
		BEAR_ASSERT(RHIFactoty);
		RHIStats = &Stats;
	}
	 
}
void RHIDestroy()
{
	BearCore::bear_delete(Factory);
	RHIFactoty = 0;
	RHIStats= 0;
}
