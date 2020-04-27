#pragma once

#include "Coffee/Core/Window.h"
#include "Coffee/Renderer/GraphicsContext.h"

#include <glfw/glfw3.h>

namespace Coffee {
	
	class WindowsWindow : public Window {
	public:

		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow() override;

		void update() override;

		unsigned getWidth() const override;
		unsigned getHeight() const override;
		
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		void* getNativeWindow() const override;

		void setEventCallbackFunc(const EventCallbackFunc& callback) override;
		
	private:

		virtual void init(const WindowProperties& properties);
		virtual void shutdown();

		virtual void setGlfwCallbacks();
		static void glfwErrorCallback(int errorCode, const char* log);
		
		GLFWwindow* _window;
		Scope<GraphicsContext> _renderContext;

		struct WindowData {
			std::string title;
			unsigned width, height;
			bool isVSync;

			EventCallbackFunc eventFunc;
		};

		WindowData _data;
	};
}
