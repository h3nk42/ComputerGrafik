#pragma once
#ifndef FLAME_CLASS_H
#define FLAME_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Model.h"
#include"shaderClass.h"

class Flame
{
public:

	glm::vec3 Position;

	Model model;

	Flame(glm::vec3 position, const char* file );

	float size = 0.0f;

	glm::vec3 OriginalOrientation = glm::vec3(0,0,-1);
	glm::vec3 Orientation = OriginalOrientation;


	void setPosition(glm::vec3 newPosition);
	void setOrientation(glm::vec3 newOrientation);

	void setSize(float newSize);



private:

	glm::vec3 flameOffset = glm::vec3(0.004f, -0.002f, 0.002f);


};


#endif
