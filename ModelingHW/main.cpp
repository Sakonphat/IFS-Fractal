// Include standard headers
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Include others OpenGL helper 
#include <common/shader.hpp>
#include <common/controls.hpp>


// -----------------------------------------------------
// windows variable
// -----------------------------------------------------

double mouseX, mouseY;
int width, height;
bool Ldown;


// -----------------------------------------------------
//+ IFS fractal
//	- width, height of the window
//	- step = #iteration of applying transformation
//	- for the return value: you should set z component to zero because we only draw 2D points
// -----------------------------------------------------

glm::vec3 IFS_triangle(int width, int height, int step) {
	
	glm::vec3 result = glm::vec3(0, 0, 0);
	
	//identityMatrix
	glm::mat4 myIdentityMatrix = glm::mat4(1.0f);
	glm::mat4 myScale,myTrans;

	

	float matrix[3][6] = {0.5f,0.0f,0.0f,0.5f,0.0f,0.0f,
		0.5f,0.0f,0.0f,0.5f,0.0f,50.0f,
		0.5f,0.0f,0.0f,0.5f,50.0f,0.0f
	};

	//float dragon[3][6] = { 0.0f	,0.577f ,-0.577f,0.0f,0.0951f,0.5893f,
	//					   0.0f,0.577f,-0.577f,0.0f,0.4413f,0.7893f,
	//					   0.0f,0.577f,-0.577f,0.0f,0.0952f,0.9893f };

	//float crystal[5][6] = { 0.382f,	0.0f,	0.0f,	0.382f,	0.3072f,	0.619f,
	//	0.382f,	0.0f,	0.0f,	0.382f,	0.6033f,	0.4044f,
	//	0.382f,	0.0f,	0.0f,	0.382f,	0.0139f,	0.4044f,
	//	0.382f,	0.0f,	0.0f,	0.382f,	0.1253f,	0.0595f,
	//	0.382f,	0.0f,	0.0f,	0.382f,	0.492f,	0.0595f };

	//float wreath[4][7] = {
	//	0.5f,   0.0f,     0.0f,     0.5f,   0.0f,     0.0f,     0.25f,
	//	0.5f,   0.5f,	  0.0f,     0.5f,   0.5f,     0.0f,     0.25f,
	//	0.5f,   0.0f,     0.5f,     0.5f,   0.0f,     0.5f,     0.25f,
	//	0.5f,   0.0f,     0.0f,     0.5f,   0.5f,     0.5f,     0.25f };

	float castle[4][7] = {
		0.5f,  0.0f,  0.0f,  0.5f,  0.0f, 0.0f,   0.25f,
		0.5f,  0.0f,  0.0f,  0.5f,  3.0f, 0.0f,   0.25f,
		0.4f,  0.0f,  0.0f,  0.4f,  0.0f, 2.0f,   0.25f,
		0.5f,  0.0f,  0.0f,  0.5f,  3.0f, 2.0f,   0.25f };

	int random = 0;
	result.x = rand() % 53;
	result.y = rand() % 52;
	for (int i = 0; i < step; i++) {
		random = rand() % 4;
		//result.x = (matrix[random][0] * result.x) + (matrix[random][1] * result.y) + matrix[random][4];
		//result.y = (matrix[random][2] * result.x) + (matrix[random][3] * result.y) + matrix[random][5];

		//result.x = (dragon[random][0] * result.x) + (dragon[random][1] * result.y) + dragon[random][4];
		//result.y = (dragon[random][2] * result.x) + (dragon[random][3] * result.y) + dragon[random][5];

		//result.x = (crystal[random][0] * result.x) + (crystal[random][1] * result.y) + crystal[random][4];
		//result.y = (crystal[random][2] * result.x) + (crystal[random][3] * result.y) + crystal[random][5];

	
		//result.x = (wreath[random][0] * result.x) + (wreath[random][1] * result.y) + wreath[random][4];
		//result.y = (wreath[random][2] * result.x) + (wreath[random][3] * result.y) + wreath[random][5];
		
		result.x = (castle[random][0] * result.x) + (castle[random][1] * result.y) + castle[random][4];
		result.y = (castle[random][2] * result.x) + (castle[random][3] * result.y) + castle[random][5];

	}
	glm::vec4 point(result.x, result.y, 0.0f,1.0f);
	myScale = glm::scale(myIdentityMatrix, glm::vec3(135.0f,135.0f, 1.0f));
	myTrans = glm::translate(myIdentityMatrix, glm::vec3(-(float(width/2)), -(float(height/2))+100, 0.0f));

	result.x = (myTrans * myScale * point).x;
	result.y = (myTrans * myScale * point).y;

	//result.x = ( myScale * point).x;
	//result.y = ( myScale * point).y;

	return result;
}




int main(void)
{
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	srand(time(NULL));
	width = 800;
	height = 800;
	Ldown = false;

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "IFS", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.2 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, width / 2, height / 2);

	// Dark background
	glViewport(0, 0, width, height);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);
	glPointSize(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	GLuint program_2Dline = LoadShaders("2Dline.vert", "2Dline.frag");
	glUseProgram(program_2Dline);

	//Create VBO
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	//Create+set VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Compute the MVP matrix for 2D
	glm::mat4 ProjectionMatrix = glm::ortho(-(width / 2)*1.0f, (width / 2)*1.0f, -(height / 2)*1.0f, (height / 2)*1.0f, -10.0f, 10.0f);
	glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program_2Dline, "MVP"), 1, GL_FALSE, &MVP[0][0]);

	glfwSwapInterval(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(window);

	float numPoint = 1;
	int speed;

	do {
		glfwPollEvents();

		// Click to clear the screen and redraw again
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			speed = 1;
		}

		// Draw numPoint each frame
		for (float i = 1; i < numPoint; i++) {

			glm::vec3 renderPoint = IFS_triangle(width, height, 10);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &renderPoint, GL_DYNAMIC_DRAW);
			glUniform3f(glGetUniformLocation(program_2Dline, "Color"), 0.5, 1, 0.5);
			glDrawArrays(GL_POINTS, 0, 1);

		}

		// Limit numPoint to draw on each frame
		if (numPoint < 300) {
			numPoint += 0.5f;
		}

		glfwSwapBuffers(window);

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);



	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(program_2Dline);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}