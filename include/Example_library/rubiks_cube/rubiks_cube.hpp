#ifndef CUSTOM_RUBIKS_CUBE
#define CUSTOM_RUBIKS_CUBE

#include <glm/glm.hpp>

class rubiks_cubie
{
public:
  glm::mat4 m;
  glm::i8vec3 opos;
};

class rubiks_cube
{
public:
  rubiks_cube();

  rubiks_cubie cubies[3][3][3];

  void rotate(char axis, char slice_idx, bool counterclockwise);

  rubiks_cubie get_cubie(char x, char y, char z);

  static const char AXIS_X, AXIS_Y, AXIS_Z;

private:
  static const glm::mat4 ROT_X_CLOCKWISE;
  static const glm::mat4 ROT_X_COUNTERCW;
  static const glm::mat4 ROT_Y_CLOCKWISE;
  static const glm::mat4 ROT_Y_COUNTERCW;
  static const glm::mat4 ROT_Z_CLOCKWISE;
  static const glm::mat4 ROT_Z_COUNTERCW;

  static const glm::mat4 ROTATION_MATRICES[];
};

#endif