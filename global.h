#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

// This is a declaration of your variable, which tells the linker this value
// is found elsewhere.  Anyone who wishes to use it must include global.h,
// either directly or indirectly.
extern float SunScale;
extern glm::vec3 SunPosition;
extern float MoonScale;
extern glm::vec3 MoonPosition;

extern std::vector <glm::vec3> planetPositions;
extern std::vector <float> planetScales;
#endif
