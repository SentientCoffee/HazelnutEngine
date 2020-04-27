#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

void Coffee::OpenGLRendererAPI::init() {
	CF_PROFILE_FUNCTION();
	
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
}

void Coffee::OpenGLRendererAPI::setViewport(const unsigned x, const unsigned y, const unsigned width, const unsigned height) {
	glViewport(x, y, width, height);
}

void Coffee::OpenGLRendererAPI::setClearColour(const glm::vec4& colour) {
	glClearColor(colour.r, colour.g, colour.b, colour.a);
}
void Coffee::OpenGLRendererAPI::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Coffee::OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray, const unsigned indexCount) {
	const unsigned count = indexCount > 0 ? indexCount : vertexArray->getIndexBuffer()->getCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
