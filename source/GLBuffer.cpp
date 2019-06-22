#include "GLPCH.h"

extern uint16 GCountIndexBuffer;
extern uint16 GCountVertexBuffer;
extern BearCore::BearMutex GBufferMutex;
GLVertexBuffer::GLVertexBuffer(void * data, bsize size, bool dynamic):Size(size),Dynamic(dynamic), Data(0)
{
	BearCore::BearMutexLock lock(GBufferMutex);
	DEBUGFATALERRORGL(glGenBuffers(1, &Buffer));
	DEBUGFATALERRORGL(glBindBuffer(GL_ARRAY_BUFFER, Buffer));
	DEBUGFATALERRORGL(glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
	GCountVertexBuffer++;
}

void * GLVertexBuffer::Lock()
{
	return Data = BearCore::bear_alloc<uint8>(Size);
}

void GLVertexBuffer::Unlock()
{
	BearCore::BearMutexLock lock(GBufferMutex);
	DEBUGFATALERRORGL(glBindBuffer(GL_ARRAY_BUFFER, Buffer));
	if (Dynamic)
	{
		DEBUGFATALERRORGL(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_DYNAMIC_DRAW));
	//	DEBUGFATALERRORGL(glBufferSubData(GL_ARRAY_BUFFER,0, Size, Data));
	}
	else
	{
		DEBUGFATALERRORGL(glBufferData(GL_ARRAY_BUFFER, Size,Data,   GL_STATIC_DRAW));
	}
	BearCore::bear_free(Data);
	Data = 0;
}

GLVertexBuffer::~GLVertexBuffer()
{
	BearCore::BearMutexLock lock(GBufferMutex);
	DEBUGFATALERRORGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	DEBUGFATALERRORGL(glDeleteBuffers(1, &Buffer));
	if(Data)BearCore::bear_free(Data);
	GCountVertexBuffer--;
}

GLIndexBuffer::GLIndexBuffer(void * data, bsize size, bool dynamic) :Size(size), Dynamic(dynamic), Data(0)
{
	BearCore::BearMutexLock lock(GBufferMutex);
	DEBUGFATALERRORGL(glGenBuffers(1, &Buffer));
	DEBUGFATALERRORGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer));
	DEBUGFATALERRORGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
	GCountIndexBuffer++;
}


void * GLIndexBuffer::Lock()
{
	return Data = BearCore::bear_alloc<uint8>(Size);
}


void GLIndexBuffer::Unlock()
{
	BearCore::BearMutexLock lock(GBufferMutex);
	DEBUGFATALERRORGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer));
	if (Dynamic)
	{
		DEBUGFATALERRORGL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Size, Data));
	}
	else
	{
		DEBUGFATALERRORGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW));
	}
	BearCore::bear_free(Data);
	Data = 0;
}

GLIndexBuffer::~GLIndexBuffer()
{
	BearCore::BearMutexLock lock(GBufferMutex);
	DEBUGFATALERRORGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	DEBUGFATALERRORGL(glDeleteBuffers(1, &Buffer));
	if (Data)BearCore::bear_free(Data);
	GCountIndexBuffer--;
}
