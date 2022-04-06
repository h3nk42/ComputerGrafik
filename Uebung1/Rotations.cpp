/* ----------------------------------------------------------------
   name:           Rotations.cpp
   purpose:        cg_ex1 
   version:	   STARTER CODE
   author:         katrin lang
                   htw berlin
------------------------------------------------------------------- */

#include <string>
#include <iostream>

#include "Context.hpp"
#include "Input.hpp"
#include "Rotations.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace std;
using namespace glm;
using namespace glsl;

const Rotations::Config Rotations::config(glm::uvec2(2, 1),
					  OpenGLApplication::Config::Profile::CORE,
					  (Window::DOUBLE | Window::DEPTH | Window::RGB | Window::MULTISAMPLE),
					  8,
					  glm::uvec2(50, 50),
					  uvec2(500, 500),
					  "cg assignment 1 - RGB cube");


Window *Rotations::window;
Mouse *Rotations::mouse;
Keyboard *Rotations::keyboard;

Shader Rotations::rgbShader;
Shader Rotations::colorTrianglesShader;

mat4 Rotations::modelMatrix= mat4(1);
mat4 Rotations::rotationMatrix= mat4(1);
mat4 Rotations::viewMatrix= mat4(1);
mat4 Rotations::projectionMatrix= mat4(1);

std::map<char, vec3> Rotations::unitVectors = std::map<char, vec3>({ {'x',vec3(1,0,0)}, {'y',vec3(0,1,0) }, {'z', vec3(0,0,1)} });



vec3 Rotations::angles = vec3(0, 0, 0);

float Rotations::fov= 45.0; // field of view
// camera setup
// camera position
GLfloat Rotations::cameraZ=5;

TriangleMesh Rotations::cube;

void Rotations::init(void){


  glClearColor(0.2, 0.2, 0.2, 1);
  
  // load rgb shader
  rgbShader.loadVertexShader("shaders/ex1/rgb-cube.vert");
  rgbShader.compileVertexShader();
  rgbShader.loadFragmentShader("shaders/ex1/rgb-cube.frag");
  rgbShader.compileFragmentShader();
  rgbShader.bindVertexAttrib("position", TriangleMesh::attribVertex);
  rgbShader.link();

  cube.load("meshes/cube.off");
}
  
void Rotations::reshape(){
  
  // Set the viewport to be the entire window
  glViewport(0, 0, window->width(), window->height());
  
  // near and far plane
  float nearPlane= cameraZ/10.0;
  float farPlane= cameraZ*10.0;

  float aspect =  ((float) window->width() / (float) window->height());
  projectionMatrix= perspective(radians(fov), aspect, nearPlane, farPlane);
  
  //position the camera at (0,0,cameraZ) looking down the
  //negative z-axis at (0,0,0)
  viewMatrix= lookAt(vec3(0.0, 0.0, cameraZ), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));

 window->redisplay();
}

void Rotations::display(void){

  glClear(GL_COLOR_BUFFER_BIT);

  static float angle= 0;
  mat4 modelMatrix= mat4(1);

  //rotate
  modelMatrix *= rotate(radians(angles.x), unitVectors['x']);
  modelMatrix *= rotate(radians(angles.y), unitVectors['y']);
  modelMatrix *= rotate(radians(angles.z), unitVectors['z']);
  cout << glm::to_string(modelMatrix) << endl;

  rgbShader.bind();
  rgbShader.setUniform("modelViewProjectionMatrix", projectionMatrix*viewMatrix*modelMatrix);
  
  cube.draw();
  
  rgbShader.unbind();

  
  glutSwapBuffers();

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



}

void Rotations::reset(void){
    angles.x = 0;
    angles.y = 0;
    angles.z = 0;
}


void Rotations::keyPressed(void){
    int angleIncrease = 90;
  
switch (keyboard->key){
    
    
  case 'Q' || 'q':
    exit(EXIT_SUCCESS);
    break;
  case 'x':
      angles.x += angleIncrease;
      window->redisplay();
      break;
  case 'y':
      angles.y += angleIncrease;
      window->redisplay();
      break;
  case 'Y':
      angles.y -= angleIncrease;
      window->redisplay();
      break;
  case 'z':
      angles.z += angleIncrease;
      window->redisplay();
      break;
  case 'r':
      reset();
      window->redisplay();
      break;
  case 'p':
      cout << glm::to_string(modelMatrix) << endl;
      break;
  default:
    return; 
  }
}


vector< pair< int, string > > Rotations::menuEntries= {{Menu::QUIT, "quit"},
                                                       {Menu::RESET, "reset"}};


void Rotations::menu(int value){
  
  switch(value){
  case Menu::QUIT:
    exit(0);
  case Menu::RESET:
    reset();
    window->redisplay();
  default: return; 
  }
}

int main(int argc, char** argv){

 
   OpenGLContext<Rotations>::init(&argc, argv);

  std::cout << "GPU: " << glGetString(GL_RENDERER) << ", OpenGL version: " << glGetString(GL_VERSION) << ", GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
   
  // start event loop
  InputManager<Rotations>::startEventLoop();
  
  return 0;
}
