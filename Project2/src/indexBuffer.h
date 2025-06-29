#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;


};

