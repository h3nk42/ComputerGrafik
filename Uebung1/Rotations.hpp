/* ----------------------------------------------------------------
   name:           Rotations.hpp
   purpose:        cg_ex1
   version:	   STARTER CODE
   author:         katrin lang
                   htw berlin
   ------------------------------------------------------------- */

#pragma once

#include <string>
#include <vector>
#include <utility>

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "GLIncludes.hpp"

#include "TriangleMesh.hpp"
#include "GLSL.hpp"
#include "Application.hpp"


class Rotations : public OpenGLApplication{
  
public:
  
  static const OpenGLApplication::Config config;
  
  static Window *window;
  static Mouse *mouse;
  static Keyboard *keyboard;
  
  //initialization
  static void init(void);
  // display
  static void display(void);
  // adjust to new window size
  static void reshape();
  // keyboard callback
  static void keyPressed(void);
  // menu handling
  static void menu(int value);
  
  // menu entries                                 
  static std::vector< std::pair< int, std::string > > menuEntries;
  
private:
    // variablen henk
    static  std::map<char, vec3> unitVectors;
    static vec3 angles;

  // reset transformations
  static void reset(void);
  
 

  static float fov, cameraZ;
  
  static glm::mat4 projectionMatrix, viewMatrix, modelMatrix, rotationMatrix;
  
  static glsl::Shader rgbShader, colorTrianglesShader;
  
  static TriangleMesh cube;
  
  struct Menu{
    enum Item{QUIT,
      RESET
    };
  };
};
