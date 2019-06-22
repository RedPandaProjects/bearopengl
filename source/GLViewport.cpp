#include "GLPCH.h"
extern uint16 GCountViewport ;
extern BearCore::BearMutex GMutexViewport;
extern BearCore::BearMutex GRenderTargerMutex;
GLViewport::GLViewport(void * win, bsize w, bsize h, bool fullscreen, bool vsync): m_fullsceen(fullscreen)
{
	GCountViewport++;
	WindowHandle = win;
	DeviceContext = GetDC((HWND)win);
	RenderContext = GLInterface::CreateRenderContext(DeviceContext);
	Resize(w, h);
	BearCore::BearMutexLock lock(GMutexViewport);
	MakeCurrent();
	DEBUGFATALERRORGL(glClearDepth(1.f));
	DEBUGFATALERRORGL(glFrontFace(GL_CW));
	DEBUGFATALERRORGL(glEnable(GL_CULL_FACE));
	DEBUGFATALERRORGL(glCullFace(GL_BACK));
	DEBUGFATALERRORGL(glGenVertexArrays(1, &VertexArray));
	DEBUGFATALERRORGL(glBindVertexArray(VertexArray));
	DEBUGFATALERRORGL(glDisable(GL_DEPTH_TEST));
	DEBUGFATALERRORGL(glDepthMask(GL_FALSE));
}

void GLViewport::Swap()
{
	BearCore::BearMutexLock lock(GMutexViewport);
	
	DEBUGFATALERRORGL(BEAR_ASSERT(SwapBuffers(DeviceContext)));
	//while (glGetError() != GL_NO_ERROR);
}

void GLViewport::SetFullScreen(bool fullscreen)
{
	BearCore::BearMutexLock lock(GMutexViewport);
	m_fullsceen = fullscreen;
	if (fullscreen)
	{
		HMONITOR hMonitor = MonitorFromWindow((HWND)WindowHandle, MONITOR_DEFAULTTOPRIMARY);
		MONITORINFOEX MonitorInfo;
		memset(&MonitorInfo, 0, sizeof(MONITORINFOEX));
		MonitorInfo.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(hMonitor, &MonitorInfo);

		DEVMODE Mode;
		Mode.dmSize = sizeof(DEVMODE);
		Mode.dmBitsPerPel = 32;
		Mode.dmPelsWidth = static_cast<DWORD>(m_screen_size.x);
		Mode.dmPelsHeight = static_cast<DWORD>(m_screen_size.y);
		Mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		
		ChangeDisplaySettingsEx(MonitorInfo.szDevice, &Mode, NULL, CDS_FULLSCREEN, NULL);
	}
	else
	{
		ChangeDisplaySettings(NULL, 0);
	}
	
}

void GLViewport::Resize(bsize w, bsize h)
{
	BearCore::BearMutexLock lock(GMutexViewport);
	m_screen_size.set(w, h);
	if (m_fullsceen)
	{
		HMONITOR hMonitor = MonitorFromWindow((HWND)WindowHandle, MONITOR_DEFAULTTOPRIMARY);
		MONITORINFOEX MonitorInfo;
		memset(&MonitorInfo, 0, sizeof(MONITORINFOEX));
		MonitorInfo.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(hMonitor, &MonitorInfo);

		DEVMODE Mode;
		Mode.dmSize = sizeof(DEVMODE);
		Mode.dmBitsPerPel = 32;
		Mode.dmPelsWidth = static_cast<DWORD>(m_screen_size.x);
		Mode.dmPelsHeight = static_cast<DWORD>(m_screen_size.y);
		Mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettingsEx(MonitorInfo.szDevice, &Mode, NULL, CDS_FULLSCREEN, NULL);
	}
	ClearColor(BearCore::BearColor::Black);
}

void GLViewport::SetVsync(bool vsync)
{
}

void GLViewport::ClearColor(const BearCore::BearColor & color)
{
	BearCore::BearMutexLock lock1(GMutexViewport);
	BearCore::BearMutexLock lock2(GRenderTargerMutex);
	MakeCurrent();
	DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	DEBUGFATALERRORGL(glDrawBuffer(GL_BACK));
	DEBUGFATALERRORGL(glClearColor(color.GetFloat()[0], color.GetFloat()[1], color.GetFloat()[2], color.GetFloat()[3]));
	DEBUGFATALERRORGL(glClear(GL_COLOR_BUFFER_BIT));

}

void GLViewport::ClearDepth(float depth)
{
	BearCore::BearMutexLock lock1(GMutexViewport);
	BearCore::BearMutexLock lock2(GRenderTargerMutex);
	MakeCurrent();
	DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	DEBUGFATALERRORGL(glClearDepth(depth));
	DEBUGFATALERRORGL(glClear(GL_DEPTH_BUFFER_BIT));


}

void GLViewport::ClearStencil(uint8 mask)
{
	BearCore::BearMutexLock lock1(GMutexViewport);
	BearCore::BearMutexLock lock2(GRenderTargerMutex);
	MakeCurrent();
	DEBUGFATALERRORGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	DEBUGFATALERRORGL(glClearStencil(mask));
	DEBUGFATALERRORGL(glClear(GL_STENCIL_BUFFER_BIT));
}

GLViewport::~GLViewport()
{
	GCountViewport--;
	BearCore::BearMutexLock lock(GMutexViewport);
	MakeCurrent();
	DEBUGFATALERRORGL(glBindVertexArray(0));
	DEBUGFATALERRORGL(glDeleteVertexArrays(1, &VertexArray));
	GLInterface::MakeCurrent();
	wglDeleteContext(RenderContext);
	ReleaseDC((HWND)WindowHandle, DeviceContext);
}

bptr GLViewport::GetRenderTarget()
{
	return 0;
}

void GLViewport::MakeCurrent()
{
	if (DeviceContext != wglGetCurrentDC() || RenderContext != wglGetCurrentContext())
		wglMakeCurrent(DeviceContext, RenderContext);
}