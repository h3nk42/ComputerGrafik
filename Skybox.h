#ifndef SKYBOX_CLASS_H
#define SKYBOX_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"
#include"shaderClass.h"




class Skybox
{
public:
	unsigned int width, height;
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;

	unsigned int cubemapTexture;

	// Initializes the mesh
	Skybox(std::string facesCubemap[6]);

	// Draws the mesh
	void Draw
	(
		unsigned int width, unsigned int height, Camera& camera, Shader& skyboxShader
	);
};
#endif
