#pragma once

#include "Core.h"

namespace Coffee {

	class COFFEE_API Input {
	public:

		static bool isKeyPressed(const int keyCode) { return _instance->isKeyPressedImpl(keyCode); };
		static bool isMouseButtonPressed(const int button) { return _instance->isMouseButtonPressedImpl(button); }

		static std::pair<float, float> getMousePosition() { return _instance->getMousePosImpl(); }
		static float getMouseX() { return _instance->getMouseXImpl(); }
		static float getMouseY() { return _instance->getMouseYImpl(); }
		
	protected:

		virtual bool isKeyPressedImpl(int keyCode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		
		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
		
	private:

		static Input* _instance;
		
	};
	
}