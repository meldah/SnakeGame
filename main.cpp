#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const GLuint SCR_WIDTH = 900;
const GLuint SCR_HEIGHT = 700;

Game SnakeGame(SCR_WIDTH, SCR_HEIGHT);

int main(int argc, char *argv[]) {
	//Initializes the GLFW library. 
	glfwInit();
	//Sets the specified window hint to the desired value.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//GLFW_OPENGL_PROFILE specifies which OpenGL profile to create the context for.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Makes the context of the specified window current for the calling thread.
	glfwMakeContextCurrent(window);	
	//Sets the framebuffer resize callback for the specified window.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	SnakeGame.Init();

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	SnakeGame.setGameState(GAME_ACTIVE);

	Shader myShader("myShader.vs", "myShader.fs");


	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;

		glfwPollEvents();


		SnakeGame.ProcessInput(window);

		if (deltaTime < 0.5) continue;
		lastFrame = currentFrame;


		SnakeGame.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		SnakeGame.Render(myShader);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}