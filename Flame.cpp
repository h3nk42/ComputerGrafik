#include"Flame.h"



Flame::Flame(glm::vec3 position, const char* filePath )
{
	Position = position;

	Model flameModel(filePath);
	model.MoveToPoint(Position +  ( -0.03f * Orientation) + flameOffset);
	model = flameModel;
	model.setScale(0.005f * size);
	model.RotateByAngle(float(90.0f), glm::vec3(1, 0, 0));
	model.RotateByAngle(float(-90.0f), glm::vec3(0, 1, 0));
	model.RotateByAngle(float(-5.0f), glm::vec3(0, 0, 1));

}

void Flame::setPosition(glm::vec3 newPosition) {
	Position = newPosition;
	model.MoveToPoint(Position + ( -0.03f * Orientation ) + flameOffset);
}

void Flame::setOrientation(glm::vec3 newOrientation)
{
	Orientation = newOrientation;


	glm::vec3 rotationAxis = glm::normalize(glm::cross(OriginalOrientation, Orientation));

	float angle = glm::orientedAngle(glm::normalize(OriginalOrientation), glm::normalize(Orientation), rotationAxis);
	std::cout << glm::degrees(angle) << std::endl;

	// Flame rotation
	model.setRotation(glm::angleAxis(angle, rotationAxis));

	model.RotateByAngle(float(90.0f), glm::vec3(1, 0, 0));
	model.RotateByAngle(float(-90.0f), glm::vec3(0, 1, 0));
	model.RotateByAngle(float(-5.0f), glm::vec3(0, 0, 1));


}

void Flame::setSize(float newSize) {

	size = glm::abs(newSize);
	model.setScale(0.0025f * size);
}




