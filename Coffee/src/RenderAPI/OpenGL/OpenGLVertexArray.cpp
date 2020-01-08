#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

#include "Coffee/Renderer/Buffers.h"

#include <glad/glad.h>

using namespace Coffee;

static GLenum shaderDataTypeToOpenGLBaseType(const ShaderDataType type) {
	switch(type) {
		case ShaderDataType::Bool:		return GL_BOOL;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Float:		return GL_FLOAT;

		case ShaderDataType::Vec2:		return GL_FLOAT;
		case ShaderDataType::Vec3:		return GL_FLOAT;
		case ShaderDataType::Vec4:		return GL_FLOAT;

		case ShaderDataType::IVec2:		return GL_INT;
		case ShaderDataType::IVec3:		return GL_INT;
		case ShaderDataType::IVec4:		return GL_INT;

		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
	}

	CF_CORE_ASSERT(false, "Unknown shader data type!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray() :
	_rendererId(0), _indexBuffer(nullptr) {
	glCreateVertexArrays(1, &_rendererId);
}

OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &_rendererId);
}

void OpenGLVertexArray::bind() const { glBindVertexArray(_rendererId); }
void OpenGLVertexArray::unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
	CF_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout!");
	
	glBindVertexArray(_rendererId);
	vertexBuffer->bind();
	
	unsigned i = 0;
	for(const auto& elem : vertexBuffer->getLayout()) {
		glEnableVertexAttribArray(i);

		glVertexAttribPointer(i, elem.getComponentCount(),
		                      shaderDataTypeToOpenGLBaseType(elem.type),
		                      elem.normalized ? GL_TRUE : GL_FALSE,
		                      vertexBuffer->getLayout().getStride(), reinterpret_cast<const void*>(elem.offset));

		++i;
	}
	
	_vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
	glBindVertexArray(_rendererId);
	indexBuffer->bind();
	
	_indexBuffer = indexBuffer;
}

const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const { return _vertexBuffers; }
const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const { return _indexBuffer; }