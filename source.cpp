#include "source.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"
#include <chrono>


void renderScene();
void initGame();

Camera* camera;
LightRenderer* light;
MeshRenderer* sphere;
MeshRenderer* ground;
btDiscreteDynamicsWorld* dynamicsWorld;


void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.0, 1.0); // clear yellow
	//light->draw();
	sphere->draw();
	ground->draw();
}

void initGame() {
	glEnable(GL_DEPTH_TEST);
	ShaderLoader shader;

	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 20.0f));

	GLuint flatShaderProgram = shader.CreateProgram("Assets/Shaders/FlatModel.vs", "Assets/Shaders/FlatModel.fs");
	GLuint texturedShaderProgram = shader.CreateProgram("Assets/Shaders/TexturedModel.vs", "Assets/Shaders/TexturedModel.fs");

	TextureLoader tLoader;
	GLuint sphereTexture = tLoader.getTextureID("Assets/Textures/globe.jpg");

	// init physics
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

	btCollisionShape* sphereShape = new btSphereShape(1.0f);
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10.0f, 0)));

	btScalar mass = 10.0;
	btVector3 sphereInertia(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);

	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);

	sphereRigidBody->setRestitution(1.0f);
	sphereRigidBody->setFriction(1.0f);


	dynamicsWorld->addRigidBody(sphereRigidBody);

	btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f,0.5f, 4.0f));
	btDefaultMotionState* groundMotionState = new	btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0, -2.0f, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f,new btDefaultMotionState(), groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setFriction(1.0);
	groundRigidBody->setRestitution(0.9);
	groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	dynamicsWorld->addRigidBody(groundRigidBody);


	// Ground Mesh
	GLuint groundTexture = tLoader.getTextureID("Assets/Textures/ground.jpg");
	ground = new MeshRenderer(MeshType::kCube, camera,groundRigidBody);
	ground->setProgram(texturedShaderProgram);
	ground->setTexture(groundTexture);
	ground->setScale(glm::vec3(4.0f, 0.5f, 4.0f));
	

	sphere = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody);
	sphere->setProgram(texturedShaderProgram);
	sphere->setTexture(sphereTexture);
	sphere->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere->setScale(glm::vec3(1.0f));


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

	auto previousTime = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(window)) {
		

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
		dynamicsWorld->stepSimulation(dt);

		renderScene();
		glfwSwapBuffers(window);
		glfwPollEvents();


		previousTime = currentTime;

	}

	glfwTerminate();

	delete camera;
	delete light;

	return 0;
}

// TODO :: ADDITION OF PHYSICS 