#include"Spaceship.h"
#include "global.h"



Spaceship::Spaceship(glm::vec3 position, const char* filePath, int _width, int _height, Camera* _camera, Flame* _flame)
{
	Position = position;
	Model spaceshipModel(filePath);
	model = spaceshipModel;
	model.setScale(0.01f);
	model.RotateByAngle(float(-90.0f), glm::vec3(1, 0, 0));
	model.RotateByAngle(float(-90.0f), glm::vec3(0, 1, 0));
	model.RotateByAngle(float(-5.0f), glm::vec3(0, 0, 1));
	


	width = _width;
	height = _height;

	camera = _camera;
	flame = _flame;

}

void Spaceship::executeMovement() {
	Position += speed * velocity * 1.3f * Orientation;
	model.MoveToPoint(Position);
		for (int i = 0; i < 8; i++) {
			if (glm::distance(Position, planetPositions[i]) < planetScales[i] + 0.05f) {
				velocity = 0;
				flame->setSize(velocity);
			}
		}
		if (glm::distance(Position, SunPosition) < SunScale + 0.1f) {
			velocity = 0;
			flame->setSize(velocity);
		}
		if (glm::distance(Position, MoonPosition) < MoonScale + 0.05f) {
			velocity = 0;
			flame->setSize(velocity);
		}
}


void Spaceship::Inputs(GLFWwindow* window)
{
	// Handles key inputs

	// apply debounce to velocity change
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
			crntVelocityChangedTime = glfwGetTime();
			double timeDiff = crntVelocityChangedTime - prevVelocityChangedTime;
			if (timeDiff > 0.2) {
				if (velocity < 6) {
					velocity++;
				}
				prevVelocityChangedTime = crntVelocityChangedTime;
				flame->setSize(velocity);
			}
	}


	// apply debounce to velocity change
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		crntVelocityChangedTime = glfwGetTime();
		double timeDiff = crntVelocityChangedTime - prevVelocityChangedTime;
		if (timeDiff > 0.2) {
			if (velocity > -1) {
				velocity--;
			}
			prevVelocityChangedTime = crntVelocityChangedTime;
			flame->setSize(velocity);
		}
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwPollEvents();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;


		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientationVertical = glm::rotate(Orientation, glm::radians(rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Cutoff vertical rotation at 45 degrees
		if (abs(glm::angle(newOrientationVertical, Up) - glm::radians(90.0f)) <= glm::radians(45.0f))
		{
			Orientation = newOrientationVertical;
		}

		// Calculates upcoming horizontal change in the Orientation
		glm::vec3 newOrientationHorizontal = glm::rotate(Orientation, glm::radians(rotY), Up);

		// update the orientation
		Orientation = newOrientationHorizontal;
		// send orientation to camera and flame so they can rotate / position accordingly
		(*camera).setOrientation(Orientation);
		(*flame).setOrientation(Orientation);


		// Spaceship rotation
		glm::vec3 rotationAxis = glm::normalize(glm::cross(
			OriginalOrientation,
			Orientation));
		float angle = glm::orientedAngle(
			glm::normalize(OriginalOrientation),
			glm::normalize(Orientation),
			rotationAxis);
		model.setRotation(glm::angleAxis(angle, rotationAxis));


		model.RotateByAngle(float(-90.0f), glm::vec3(1, 0, 0));
		model.RotateByAngle(float(-90.0f), glm::vec3(0, 1, 0));
		model.RotateByAngle(float(-5.0f), glm::vec3(0, 0, 1));


		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}

	
}

