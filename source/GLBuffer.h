#pragma once
class GLIndexBuffer:public BearRHI::BearRHIIndexBuffer
{
public:
	GLIndexBuffer(void*data,bsize size,bool dynamic);
	virtual void*Lock();
	virtual void Unlock();
	~GLIndexBuffer();
	GLuint Buffer;
	bsize Size;
	void* Data;
	bool Dynamic;
private:
};

class GLVertexBuffer:public BearRHI::BearRHIVertexBuffer
{
public:
	GLVertexBuffer(void*data, bsize size, bool dynamic);
	virtual void*Lock();
	virtual void Unlock();
	~GLVertexBuffer();
	GLuint Buffer;
	bsize Size;
	void* Data;
	bool Dynamic;
private:
};

