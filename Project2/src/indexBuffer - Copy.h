#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const void* data,unsigned int size);
	~IndexBuffer();
	void Bind();
	void Unbind();

private:
	unsigned int m_RendererID;

};

