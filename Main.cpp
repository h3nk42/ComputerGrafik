//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<Windows.h>
#include<MMSystem.h>
#include<iostream>

using namespace std;
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include"Model.h"
#include"Skybox.h"
#include"Spaceship.h"
#include"Flame.h"
#include "global.h"


//define size of window
const unsigned int width = 1920;
const unsigned int height = 1080;

//initilize score
int score = 0;

glm::vec3 spaceshipPosition = glm::vec3(20.0f, 0.f, 10.f);


// get the current path for relative imports
std::string homeDir = fs::current_path().string();


std::vector<std::string> planetNames = { "mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"};

glm::vec3 SunPosition = glm::vec3(0.0f, 0.0f, 0.0f);
float SunScale = 10.0f;

glm::vec3 MercuyPosition = glm::vec3(10.0f + 4.10f, 0.0f, 0.0f);
float MercuryScale = 0.035f;

glm::vec3 VenusPosition = glm::vec3(10.0f + 7.70f, 0.0f, 0.0f);
float VenusScale = 0.086f;

glm::vec3 EarthPosition = glm::vec3(10.0f + 10.70f, 0.0f, 0.0f);
float EarthScale = 0.091f;


glm::vec3 MoonPosition = glm::vec3(10.0f + 10.7275f, 0.1f, 0.0f);
float MoonScale = 0.025f;

glm::vec3 MarsPosition = glm::vec3(10.0f + 16.30f, 0.0f, 0.0f);
float MarsScale = 0.049f;


glm::vec3 JupiterPosition = glm::vec3(10.0f + 55.60f, 0.0f, 0.0f);
float JupiterScale = 1.02f;


glm::vec3 SaturnPosition = glm::vec3(10.0f + 101.90f, 0.0f, 0.0f);
float SaturnScale = 0.86f;


glm::vec3 UranusPosition = glm::vec3(205.10f, 0.0f, 0.0f);
float UranusScale = 0.37f;


glm::vec3 NeptunePosition = glm::vec3(321.30f, 0.0f, 0.0f);
float NeptuneScale = 0.35f;


std::vector <glm::vec3> planetPositions = { MercuyPosition,VenusPosition,EarthPosition,MarsPosition, JupiterPosition, SaturnPosition, UranusPosition, NeptunePosition };
std::vector <float> planetScales = { MercuryScale,VenusScale,EarthScale,MarsScale, JupiterScale, SaturnScale, UranusScale, NeptuneScale };
uint8_t activePlanetIndex = 0;



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


	// Create a GLFWwindow object of 800 by 800 pixels, naming it "Solar System"
	GLFWwindow* window = glfwCreateWindow(width, height, "Solar System", NULL, NULL);
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


	// Initialize camera and flame
	Camera camera(width, height, spaceshipPosition);
	Flame flame(spaceshipPosition, (homeDir + "/resources/flame/scene.gltf").c_str());

	// Initialize the spaceship with camera and flame pointers
	Spaceship spaceship(spaceshipPosition, (homeDir + "/resources/spaceship/scene.gltf").c_str(), width, height, &camera, &flame);

	srand(time(NULL));

	activePlanetIndex = rand() % 8;

	// Set up planets positions and scales
	Model sun((homeDir + "/resources/planets/sun/scene.gltf").c_str());
	sun.MoveToPoint(SunPosition);
	sun.setScale(SunScale);

	Model mercury((homeDir + "/resources/planets/mercury/scene.gltf").c_str());

	planetPositions.push_back(MercuyPosition);
	mercury.MoveToPoint(MercuyPosition);
	mercury.setScale(MercuryScale);

	Model venus((homeDir + "/resources/planets/venus/scene.gltf").c_str());

	venus.MoveToPoint(VenusPosition);
	venus.setScale(VenusScale);

	Model earth((homeDir + "/resources/planets/earth/scene.gltf").c_str());

	earth.MoveToPoint(EarthPosition);
	earth.setScale(EarthScale);

	Model moon((homeDir + "/resources/planets/moon/scene.gltf").c_str());

	moon.MoveToPoint(MoonPosition);
	moon.setScale(MoonScale);

	Model mars((homeDir + "/resources/planets/mars/scene.gltf").c_str());

	mars.MoveToPoint(MarsPosition);
	mars.setScale(MarsScale);

	Model jupiter((homeDir + "/resources/planets/jupiter/scene.gltf").c_str());

	jupiter.MoveToPoint(JupiterPosition);
	jupiter.setScale(JupiterScale);

	Model saturn((homeDir + "/resources/planets/saturn/scene.gltf").c_str());

	saturn.MoveToPoint(SaturnPosition);
	saturn.setScale(SaturnScale);

	Model uranus((homeDir + "/resources/planets/uranus/scene.gltf").c_str());

	uranus.MoveToPoint(UranusPosition);
	uranus.setScale(UranusScale);

	Model neptune((homeDir + "/resources/planets/neptune/scene.gltf").c_str());

	neptune.MoveToPoint(NeptunePosition);
	neptune.setScale(NeptuneScale);


	std::string facesCubemap[6] =
	{
		homeDir + "/resources/skybox2/right.jpg",
		homeDir + "/resources/skybox2/left.jpg",
		homeDir + "/resources/skybox2/top.jpg",
		homeDir + "/resources/skybox2/bottom.jpg",
		homeDir + "/resources/skybox2/front.jpg",
		homeDir + "/resources/skybox2/back.jpg"
	};

	std::string songSource = homeDir + "/resources/sounds/open-space.wav";
	std::wstring backgroundSound = std::wstring(songSource.begin(), songSource.end());

	PlaySound(backgroundSound.data(), NULL, SND_SYSTEM | SND_ASYNC);

	Skybox skybox(facesCubemap);


	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	// Use this to disable VSync (not advized)
	//glfwSwapInterval(0);


	glm::vec3 prevCameraPosition = camera.Position;

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{


		// Updates counter and times
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		// set window title
		std::string titleBegin = "Fly to: < ";
		std::string titleEnd = " > !";
		std::string successSource = homeDir + "/resources/sounds/shooting_star.wav";
		std::wstring successSound = std::wstring(successSource.begin(), successSource.end());
		//if you are using unicode
		//std::string a = "open " + successSource + " type mpegvideo";
		//std::wstring stemp = std::wstring(a.begin(), a.end());
		std::string b = "play " + successSource;
		std::wstring stempb = std::wstring(b.begin(), b.end());

		//std::cout << successSource;
		//std::string c = "close " + successSource;
		//std::wstring stempc = std::wstring(c.begin(), c.end());

		if (glm::distance(spaceshipPosition, planetPositions[activePlanetIndex]) < planetScales[activePlanetIndex] + 0.5f) {
			activePlanetIndex = rand() % 8;
			score += 10;
			mciSendString(stempb.data(), NULL, 0, 0);
		}


		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		// Handles camera inputs (delete this if you have disabled VSync)
		spaceship.Inputs(window);
		spaceship.executeMovement();
		spaceshipPosition = spaceship.Position;
		camera.setPosition(spaceshipPosition);
		flame.setPosition(spaceshipPosition);

		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.025f, 1000.0f);


		// Draw the models and rotate the planets;
		spaceship.model.Draw(shaderProgram, camera);
		flame.model.Draw(sunShader, camera);

		sun.Draw(sunShader, camera);
		sun.RotateByAngle(0.0005f, glm::vec3(0.0f, 0.5f, 0.5f));

		mercury.Draw(shaderProgram, camera);
		mercury.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		earth.Draw(shaderProgram, camera);
		earth.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		moon.Draw(shaderProgram, camera);
		moon.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		mars.Draw(shaderProgram, camera);
		mars.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		jupiter.Draw(shaderProgram, camera);
		jupiter.RotateByAngle(0.1f, glm::vec3(0.0f, 0.5f, 0.5f));

		saturn.Draw(shaderProgram, camera);
		saturn.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		uranus.Draw(shaderProgram, camera);
		uranus.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		venus.Draw(shaderProgram, camera);
		venus.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		neptune.Draw(shaderProgram, camera);
		neptune.RotateByAngle(0.01f, glm::vec3(0.0f, 0.5f, 0.5f));

		// Draw the skybox
		skybox.Draw(width, height, camera, skyboxShader);


		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 450.f,150.f });

		// ImGUI window creation
		ImGui::Begin("Missions to be done:", nullptr, ImGuiWindowFlags_NoCollapse);
		ImGui::SetNextWindowPos(ImVec2(80, 80));
		ImGui::PopStyleVar(1);
		//ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

		// Text that appears in the window
		std::string scoreString = std::to_string(score);

		if (score == 80) {
			ImGui::Text("Congratulations, you\ndiscovered the whole\nsolar system!!");
		}
		else ImGui::Text((titleBegin + planetNames[activePlanetIndex] + titleEnd + "\n\nScore: " + scoreString).c_str());
		ImGui::SetWindowFontScale(3);


		// Ends the window
		ImGui::End();
		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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