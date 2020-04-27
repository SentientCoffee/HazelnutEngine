#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLBuffers.h"

#include <glad/glad.h>

using namespace Coffee;

// ----------------------------------------
// ----- Vertex buffers -------------------
// ----------------------------------------

OpenGLVertexBuffer::OpenGLVertexBuffer(const unsigned size) :
	_rendererId(0)
{
	CF_PROFILE_FUNCTION();
	glCreateBuffers(1, &_rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, const unsigned size) :
	_rendererId(0)
{
	CF_PROFILE_FUNCTION();
	glCreateBuffers(1, &_rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
	CF_PROFILE_FUNCTION();
	glDeleteBuffers(1, &_rendererId);
}

void OpenGLVertexBuffer::bind() const { CF_PROFILE_FUNCTION(); glBindBuffer(GL_ARRAY_BUFFER, _rendererId); }
void OpenGLVertexBuffer::unbind() const { CF_PROFILE_FUNCTION(); glBindBuffer(GL_ARRAY_BUFFER, 0); }

void OpenGLVertexBuffer::setData(const void* data, const unsigned size) {
	CF_PROFILE_FUNCTION();
	glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::setLayout(const BufferLayout& layout) { _layout = layout; }
const BufferLayout& OpenGLVertexBuffer::getLayout() const { return _layout; }

// ----------------------------------------
// ----- Index buffers --------------------
// ----------------------------------------

OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned* indices, const unsigned count) :
	_rendererId(0), _indexCount(count)
{
	CF_PROFILE_FUNCTION();
	glCreateBuffers(1, &_rendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
	CF_PROFILE_FUNCTION();
	glDeleteBuffers(1, &_rendererId);
}

void OpenGLIndexBuffer::bind() const { CF_PROFILE_FUNCTION(); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId); }
void OpenGLIndexBuffer::unbind() const { CF_PROFILE_FUNCTION(); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

unsigned OpenGLIndexBuffer::getCount() const { return _indexCount; }
