#include "GLPCH.h"
#ifdef WINDOWS

static LRESULT CALLBACK WindowsPROC(HWND hWnd, uint32 Message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Message, wParam, lParam);
}

HWND  GLInterface::WindowHandle=0;
HDC  GLInterface::DeviceContext=0;
HGLRC  GLInterface::RenderContext=0;

static bool LInitWindowsClass = false;
static HWND CreateWindows()
{
	if (!LInitWindowsClass)
	{
		LInitWindowsClass = true;
		WNDCLASS wc;
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WindowsPROC;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = NULL;
		wc.hIcon = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = (HBRUSH)(COLOR_MENUTEXT);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = TEXT("TEST_GL");
		RegisterClass(&wc);
	}
	return  CreateWindowEx(
		WS_EX_WINDOWEDGE,
		TEXT("TEST_GL"),
		NULL,
		WS_POPUP,
		0, 0, 1, 1,
		NULL, NULL, NULL, NULL);
}

void GLInterface::InitializePlatform()
{
	RenderContext = 0;
	WindowHandle = CreateWindows();
	DeviceContext = GetDC(WindowHandle);
	RenderContext = CreateRenderContext(DeviceContext);
	BEAR_RASSERT(DeviceContext&&RenderContext);
	BEAR_RASSERT(wglMakeCurrent(DeviceContext, RenderContext));
}

void GLInterface::DestroyPlatform()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(RenderContext);
	RenderContext = NULL;
	ReleaseDC((HWND)WindowHandle, DeviceContext);
	DeviceContext = 0;
	DestroyWindow(WindowHandle);
}

bool GLInterface::IsSupport()
{
	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error;
	HGLRC renderContext;
	bool result;


	HWND hwnd = CreateWindows();
	BEAR_RASSERT(hwnd);
	deviceContext = GetDC((HWND)hwnd);
	if (!deviceContext)
	{
		return false;
	}

	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		return false;
	}

	renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		return false;
	}
	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		return false;
	}

	result = GetFunction();
	if (!result)
	{
		return false;
	}

	GLint Major, Minor;
	FATALERRORGL( glGetIntegerv(GL_MAJOR_VERSION, &Major));
	FATALERRORGL(glGetIntegerv(GL_MINOR_VERSION, &Minor));
	if (Major < 4 || Minor < 2)
		return false;

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;

	// Release the device context for this window.
	ReleaseDC((HWND)hwnd, deviceContext);
	deviceContext = 0;
	DestroyWindow(hwnd);
	return true;
}

HGLRC GLInterface::CreateRenderContext(HDC Device)
{

	PIXELFORMATDESCRIPTOR PixelFormatDesc;
	BearCore::bear_fill(PixelFormatDesc);
	PixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	PixelFormatDesc.nVersion = 1;
	PixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	PixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	PixelFormatDesc.cColorBits = 32;
	PixelFormatDesc.cDepthBits = 0;
	PixelFormatDesc.cStencilBits = 0;
	PixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
	int PixelAttribList[] =
	{
		WGL_SUPPORT_OPENGL_ARB,
		TRUE,
		WGL_DRAW_TO_WINDOW_ARB,
		TRUE,
		WGL_ACCELERATION_ARB,
		WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB,
		24,
		WGL_DEPTH_BITS_ARB,
		24,
		WGL_DOUBLE_BUFFER_ARB,
		TRUE,
		WGL_SWAP_METHOD_ARB,
		WGL_SWAP_EXCHANGE_ARB,
		WGL_PIXEL_TYPE_ARB,
		WGL_TYPE_RGBA_ARB,

		WGL_STENCIL_BITS_ARB,8
		,0
	};
	int32 PixelFormat;
	unsigned int formatCount;
	BEAR_RASSERT(wglChoosePixelFormatARB(Device, PixelAttribList, 0,1, &PixelFormat,&formatCount));
	BEAR_RASSERT(PixelFormat &&SetPixelFormat(Device, PixelFormat, &PixelFormatDesc));
	int DebugFlag = 0;

#ifdef _DEBUG
	DebugFlag = WGL_CONTEXT_DEBUG_BIT_ARB;
#endif 

	int AttribList[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB,static_cast<int>(3),
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | DebugFlag,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,

		0
	};

	return wglCreateContextAttribsARB(Device, RenderContext, AttribList);
}

void GLInterface::MakeCurrent()
{
	BEAR_RASSERT(wglMakeCurrent(DeviceContext, RenderContext));
}


#endif