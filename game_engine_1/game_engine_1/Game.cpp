#include "Game.h"

double Game::xpos = 0;
double Game::ypos = 0;

Game::Game() {
	this->glHandler = new GLhandler();
	this->glHandler->init();
	this->glHandler->set_mouse_callback((GLFWcursorposfun)Game::mouse_callback);
	
	ShaderProgram *shaderProgram = new ShaderProgram("./Shaders/texture_vertex_shader.txt", "./Shaders/texture_fragment_shader.txt");
	this->ambient = new Ambient(shaderProgram);

	this->lastX = this->lastY = this->yaw = this->pitch = 0.0f;
	this->firstMouse = false;
}

Game::~Game() {
}

void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	Game::xpos = xpos;
	Game::ypos = ypos;
}

void Game::process_input(LightSource *lamp) {
	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->glHandler->getWindow(), true);
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		this->ambient->camera->moveFront();
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		this->ambient->camera->moveBack();
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		this->ambient->camera->moveRight();
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		this->ambient->camera->moveLeft();
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		lamp->translate(glm::vec3(0.001f, 0.0f, 0.0f));
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		lamp->translate(glm::vec3(-0.001f, 0.0f, 0.0f));
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
		lamp->translate(glm::vec3(0.0f, 0.0f, -0.001f));
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		lamp->translate(glm::vec3(0.0f, 0.0f, 0.001f));
	}

	if (glfwGetKey(this->glHandler->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) //Checks if ESCAPE key is currently being pressed;
		this->ambient->camera->setTarget(glm::vec3(0.0f, 0.0f, -1.0f));


	//MOUSE INPUT

	if (this->firstMouse)
	{
		this->lastX = Game::xpos;
		this->lastY = Game::ypos;
		this->firstMouse = false;
	}

	float xoffset = Game::xpos - this->lastX;
	float yoffset = this->lastY - Game::ypos;
	this->lastX = Game::xpos;
	this->lastY = Game::ypos;

	float sensitivity = 0.05f;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->ambient->camera->update(this->yaw, this->pitch);
}

void Game::setup() {
	this->running = true;
}

void Game::start() {

	float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f
 	};
	float greenCubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f
	};

	ObjectModel *wooden_cube = new ObjectModel(sizeof(cubeVertices), cubeVertices, 0, 3, -1, 5, "./Textures/container.jpg");
	ObjectModel *green_cube = new ObjectModel(sizeof(greenCubeVertices), greenCubeVertices, 0, -1, 3, 6);

	Object *cube1 = new Object(wooden_cube);
	Object *cube2 = new Object(wooden_cube);
	Object *cube3 = new Object(wooden_cube);
	Object *cube4 = new Object(green_cube);
	cube1->translate(glm::vec3(2.0f, 0.0f, 0.0f));
	cube1->scale = glm::vec3(0.5, 0.5, 0.5);
	cube2->translate(glm::vec3(0.0f, 5.0f, -3.0f));
	cube3->translate(glm::vec3(1.0f, 3.0f, 3.0f));
	cube4->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	
	LightSource *lightSource1 = new LightSource(green_cube, glm::vec3(1.0, 1.0, 1.0));
	lightSource1->scale = glm::vec3(0.05, 0.05, 0.05);
	lightSource1->translate(glm::vec3(5.0f, 0.0f, 0.0f));

	ambient->add_object(cube1);
	ambient->add_object(cube2);
	ambient->add_object(cube3);
	ambient->add_object(cube4);
	ambient->add_light_source(lightSource1);
	
	while (this->running) {
		if (glfwWindowShouldClose(this->glHandler->getWindow())) {
			this->running = false;
		}

		this->process_input(lightSource1);
		this->ambient->camera->adjustCameraSpeed(glfwGetTime());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->ambient->draw();
	
		glfwSwapBuffers(this->glHandler->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();
}