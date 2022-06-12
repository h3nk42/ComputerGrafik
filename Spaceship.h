#ifndef SPACESHIP_CLASS_H
#define SPACESHIP_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Model.h"
#include"shaderClass.h"

class Spaceship
{
public:

	glm::vec3 Position;

	Model model;

	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	float velocity = 0.0f;

	float speed = 0.05f;


	Spaceship(glm::vec3 position, const char* file, int width, int height, Camera* camera);

	void Inputs(GLFWwindow* window);

	void executeMovement();
private:
	double prevVelocityChangedTime = 0.0;
	double crntVelocityChangedTime = 0.0;


	// Stores the width and height of the window
	int width;
	int height;

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	float sensitivity = 100.0f;

	Camera* camera;

};


#endif
