#include"Spaceship.h"



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
	Position += speed * velocity * Orientation;
	model.MoveToPoint(Position);
}


void Spaceship::Inputs(GLFWwindow* window)
{
	// Handles key inputs
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
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		model.RotateByAngle(1.0f,glm::vec3(1,0,0));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		model.RotateByAngle(-1.0f,glm::vec3(1,0,0));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		model.RotateByAngle(1.0f, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		model.RotateByAngle(-1.0f, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		crntVelocityChangedTime = glfwGetTime();
		double timeDiff = crntVelocityChangedTime - prevVelocityChangedTime;
		if (timeDiff > 0.2) {
			if (velocity > 0) {
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

		if (abs(glm::angle(newOrientationVertical, Up) - glm::radians(90.0f)) <= glm::radians(45.0f))
		{
			Orientation = newOrientationVertical;
		}


		glm::vec3 newOrientationHorizontal = glm::rotate(Orientation, glm::radians(rotY), Up);

		Orientation = newOrientationHorizontal;
		(*camera).setOrientation(Orientation);
		(*flame).setOrientation(Orientation);

		glm::vec3 rotationAxis = glm::normalize(glm::cross(OriginalOrientation, Orientation));

		
		float angle = glm::orientedAngle(glm::normalize(OriginalOrientation), glm::normalize(Orientation), rotationAxis);
		std::cout << glm::degrees(angle) << std::endl;

		// Spaceship rotation
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

