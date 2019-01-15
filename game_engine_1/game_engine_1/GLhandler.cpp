#include "GLhandler.h"

GLhandler::GLhandler() {

}


GLhandler::~GLhandler()
{
}

GLFWwindow *GLhandler::getWindow() {
	return this->window;
}

void GLhandler::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void GLhandler::set_mouse_callback(GLFWcursorposfun mouse_callback) {
	this->mouse_callback = mouse_callback;
	glfwSetCursorPosCallback(window, this->mouse_callback);
}

int GLhandler::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
	if (this->window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, GLhandler::framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

}