//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include"Model.h"
#include"Skybox.h"

//define size of window
const unsigned int width = 1920;
const unsigned int height = 1080;

// get the current path for relative imports
std::string homeDir = fs::current_path().string();



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);





	// Generates Shader objects
	Shader shaderProgram("default.vert", "default.frag");
	Shader skyboxShader("skybox.vert", "skybox.frag");
	Shader sunShader("default.vert", "sun.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(10.0f, 0.0f, 0.0f);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	sunShader.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);


	
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Enables Cull Facing
	glEnable(GL_CULL_FACE);
	// Keeps front faces
	glCullFace(GL_FRONT);
	// Uses counter clock-wise standard
	glFrontFace(GL_CCW);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 50.0f));



	// Load in spaceship
	Model spaceship((homeDir + "/resources/spaceship/scene.gltf").c_str());
	spaceship.Move(glm::vec3(0.0f, -50.0f, 5.0f));
	Model flame((homeDir + "/resources/flame/scene.gltf").c_str());
	flame.Move(glm::vec3(-51.0f, 0.0f, -5.0f));
	//flame.Rotate(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f));



	Model sun((homeDir + "/resources/planets/sun/scene.gltf").c_str());
	sun.Move(glm::vec3(0.0f, 0.0f, 0.0f));
	sun.Scale(10.0f);

	Model mercury((homeDir + "/resources/planets/mercury/scene.gltf").c_str());
	mercury.Move(glm::vec3( 10.0f + 4.10f, 0.0f, 0.0f));
	mercury.Scale(0.035f);

	Model venus((homeDir + "/resources/planets/venus/scene.gltf").c_str());
	venus.Move(glm::vec3(10.0f + 7.70f, 0.0f, 0.0f));
	venus.Scale(0.086f);

	Model earth((homeDir + "/resources/planets/earth/scene.gltf").c_str());
	earth.Move(glm::vec3(10.0f + 10.70f, 0.0f, 0.0f));
	earth.Scale(0.091f);

	Model moon((homeDir + "/resources/planets/moon/scene.gltf").c_str());
	moon.Move(glm::vec3(10.0f  + 10.7275f, 0.1f, 0.0f));
	moon.Scale(0.025f);

	Model mars((homeDir + "/resources/planets/mars/scene.gltf").c_str());
	mars.Move(glm::vec3(10.0f + 16.30f, 0.0f, 0.0f));
	mars.Scale(0.049f);

	Model jupiter((homeDir + "/resources/planets/jupiter/scene.gltf").c_str());
	jupiter.Move(glm::vec3(10.0f + 55.60f, 0.0f, 0.0f));
	jupiter.Scale(1.02f);

	Model saturn((homeDir + "/resources/planets/saturn/scene.gltf").c_str());
	saturn.Move(glm::vec3(10.0f + 101.90f, 0.0f, 0.0f));
	saturn.Scale(0.86f);

	Model uranus((homeDir + "/resources/planets/uranus/scene.gltf").c_str());
	uranus.Move(glm::vec3(205.10f, 0.0f, 0.0f));
	uranus.Scale(0.37f);
	
	Model neptune((homeDir + "/resources/planets/neptune/scene.gltf").c_str());
	neptune.Move(glm::vec3(321.30f, 0.0f, 0.0f));
	neptune.Scale(0.35f);



	



	std::string facesCubemap[6] =
	{
		homeDir + "/resources/skybox2/right.jpg",
		homeDir + "/resources/skybox2/left.jpg",
		homeDir + "/resources/skybox2/top.jpg",
		homeDir + "/resources/skybox2/bottom.jpg",
		homeDir + "/resources/skybox2/front.jpg",
		homeDir + "/resources/skybox2/back.jpg"
	};

	Skybox skybox(facesCubemap);


	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	// Use this to disable VSync (not advized)
	//glfwSwapInterval(0);





	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Updates counter and times
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "cg_beleg - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;

			// Use this if you have disabled VSync
			//camera.Inputs(window);
		}

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs (delete this if you have disabled VSync)
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		spaceship.Move(glm::vec3(0.0f, 0.02f, 0.0f));
		flame.Move(glm::vec3(0.02f, 0.00f, 0.0f));

		// Draw the normal model
		spaceship.Draw(shaderProgram, camera);
		flame.Draw(shaderProgram, camera);

		sun.Draw(sunShader, camera);
		sun.Rotate(0.0005f, glm::vec3(0.0f, 0.5f, 0.5f));

		mercury.Draw(shaderProgram, camera);
		mercury.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));


		earth.Draw(shaderProgram, camera);
		earth.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		moon.Draw(shaderProgram, camera);
		moon.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		mars.Draw(shaderProgram, camera);
		jupiter.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));


		jupiter.Draw(shaderProgram, camera);
		jupiter.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		saturn.Draw(shaderProgram, camera);
		saturn.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		uranus.Draw(shaderProgram, camera);
		uranus.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		venus.Draw(shaderProgram, camera);
		venus.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		neptune.Draw(shaderProgram, camera);
		neptune.Rotate(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

	

		// Draw the skybox
		skybox.Draw(width, height, camera, skyboxShader);

		


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();
	skyboxShader.Delete();
	sunShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}