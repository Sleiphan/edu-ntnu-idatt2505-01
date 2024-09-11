// #define GLM_FORCE_SWIZZLE

#include "Example_library/rubiks_cube/rubiks_cube.hpp"
#include <utility>

const glm::mat4 rubiks_cube::ROT_X_CLOCKWISE = glm::mat4(glm::i8vec4(1, 0, 0, 0),
                                                         glm::i8vec4(0, 0, -1, 0),
                                                         glm::i8vec4(0, 1, 0, 0),
                                                         glm::i8vec4(0, 0, 0, 1));

const glm::mat4 rubiks_cube::ROT_X_COUNTERCW = glm::mat4(glm::i8vec4(1, 0, 0, 0),
                                                         glm::i8vec4(0, 0, 1, 0),
                                                         glm::i8vec4(0, -1, 0, 0),
                                                         glm::i8vec4(0, 0, 0, 1));

const glm::mat4 rubiks_cube::ROT_Y_CLOCKWISE = glm::mat4(glm::i8vec4(0, 0, 1, 0),
                                                         glm::i8vec4(0, 1, 0, 0),
                                                         glm::i8vec4(-1, 0, 0, 0),
                                                         glm::i8vec4(0, 0, 0, 1));

const glm::mat4 rubiks_cube::ROT_Y_COUNTERCW = glm::mat4(glm::i8vec4(0, 0, -1, 0),
                                                         glm::i8vec4(0, 1, 0, 0),
                                                         glm::i8vec4(1, 0, 0, 0),
                                                         glm::i8vec4(0, 0, 0, 1));

const glm::mat4 rubiks_cube::ROT_Z_CLOCKWISE = glm::mat4(glm::i8vec4(0, 1, 0, 0),
                                                         glm::i8vec4(-1, 0, 0, 0),
                                                         glm::i8vec4(0, 0, 1, 0),
                                                         glm::i8vec4(0, 0, 0, 1));

const glm::mat4 rubiks_cube::ROT_Z_COUNTERCW = glm::mat4(glm::i8vec4(0, 1, 0, 0),
                                                         glm::i8vec4(-1, 0, 0, 0),
                                                         glm::i8vec4(0, 0, 1, 0),
                                                         glm::i8vec4(0, 0, 0, 1));

const char rubiks_cube::AXIS_X = 0;
const char rubiks_cube::AXIS_Y = 1;
const char rubiks_cube::AXIS_Z = 2;

const glm::mat4 rubiks_cube::ROTATION_MATRICES[] = {
    ROT_X_CLOCKWISE,
    ROT_X_COUNTERCW,
    ROT_Y_CLOCKWISE,
    ROT_Y_COUNTERCW,
    ROT_Z_CLOCKWISE,
    ROT_Z_COUNTERCW};

rubiks_cube::rubiks_cube()
{
  for (char z = 0; z < 3; ++z)
    for (char y = 0; y < 3; ++y)
      for (char x = 0; x < 3; ++x)
      {
        cubies[z][y][x] = glm::mat4(1.0f);
        cubies[z][y][x][3] = glm::vec4(x - 1, y - 1, z - 1, 1.0f);
      }
}

glm::mat4 rubiks_cube::get_cubie(char x, char y, char z)
{
  return cubies[z + 1][y + 1][x + 1];
}

void rubiks_cube::rotate(char axis, char plane_idx, bool counterclockwise)
{
  glm::mat4 rot_matrix = ROTATION_MATRICES[axis * 2 + counterclockwise];

  // The variables used to access cubies
  char x = 0, y = 0, z = 0;

  // The handles used to iterate over a plane of cubies
  char *a, *b, *c;

  // Set the handles correctly according to axis
  switch (axis)
  {
  case AXIS_X:
    a = &z;
    b = &y;
    c = &x;
    break;
  case AXIS_Y:
    a = &z;
    b = &x;
    c = &y;
    break;
  case AXIS_Z:
    a = &y;
    b = &x;
    c = &z;
    break;
  }

  // Set the plane. This value will be constant
  *c = plane_idx;

  // Apply rotation on relevant cubes
  for (*a = 0; *a < 3; ++*a)
    for (*b = 0; *b < 3; ++*b)
      cubies[z][y][x] = rot_matrix * cubies[z][y][x];

  // Move the cubes to their correct location
  for (*a = 0; *a < 3; ++*a)
    for (*b = 0; *b < 3; ++*b)
    {
      glm::i8vec3 p(x - 1, y - 1, z - 1);
      glm::i8vec3 t = cubies[z][y][x][3];

      while (p != t)
      {
        std::swap(cubies[z][y][x], cubies[t.z + 1][t.y + 1][t.x + 1]);
        t = cubies[z][y][x][3];
      }
    }
}