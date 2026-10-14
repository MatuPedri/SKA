#pragma once 
#include "common.hpp"

struct GLFWwindow;
namespace ska {
		class Window {
		public:
				Window(const u16 w, const u16 h);
				~Window();
				Window(const Window&) = delete;
				Window& operator=(const Window&) = delete;
				/*void create();
				void destroy();*/
				bool isClosed() const;
				void swap();
				void pollEvents();
				GLFWwindow* handle() const;

				u16 getWidth() const { return width_; }
				u16 getHeight() const { return height_; }

		protected:
			u16 width_;
			u16 height_;
		private:
			GLFWwindow* glfw_window_ = nullptr;
		};
}