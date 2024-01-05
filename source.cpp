#include "source.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"


void renderScene();
void initGame();

Camera* camera;
LightRenderer* light;


void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.0, 1.0); // clear yellow
	light->draw();
}

void initGame() {
	glEnable(GL_DEPTH_TEST);
	ShaderLoader shader;

	GLuint flatShaderProgram = shader.CreateProgram("Assets/Shaders/FlatModel.vs", "Assets/Shaders/FlatModel.fs");
	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));

	light = new LightRenderer(MeshType::kCube, camera);
	light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}


int main(int argc, char** argv) {
	glfwInit();


	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL ", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	initGame();

	while (!glfwWindowShouldClose(window)) {
		renderScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	delete camera;
	delete light;

	return 0;
}
