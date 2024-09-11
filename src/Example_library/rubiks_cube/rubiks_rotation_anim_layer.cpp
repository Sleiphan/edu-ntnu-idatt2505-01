#include "Example_library/rubiks_cube/rubiks_rotation_anim_layer.hpp"
#include "Example_library/rubiks_cube/rubiks_cube.hpp"
#include <glm/ext/matrix_transform.hpp>

rubiks_rotation_anim_layer::rubiks_rotation_anim_layer() : axis(-1), plane_idx(-1), transformation(glm::mat4(1.0f)) {}

void rubiks_rotation_anim_layer::rotate(char axis, char plane_idx, float angle)
{
  this->axis = axis;
  this->plane_idx = plane_idx;
  this->transformation = glm::rotate(
      glm::mat4(1.0f),
      angle,
      glm::vec3(
          axis == 0,
          axis == 1,
          axis == 2));
}

void rubiks_rotation_anim_layer::apply_transformation(glm::mat4 cubies[3][3][3])
{
  uint8_t x = 0, y = 0, z = 0;
  uint8_t *a, *b, *c;

  switch (axis)
  {
  case 0:
    a = &z;
    b = &y;
    c = &x;
    break;
  case 1:
    a = &z;
    b = &x;
    c = &y;
    break;
  case 2:
    a = &y;
    b = &x;
    c = &z;
    break;
  }

  *c = plane_idx;

  for (*a = 0; *a < 3; ++(*a))
    for (*b = 0; *b < 3; ++(*b))
      cubies[z][y][x] = transformation * cubies[z][y][x];
}

glm::mat4 rubiks_rotation_anim_layer::get_transformation(char x, char y, char z)
{
  char *coord;

  switch (axis)
  {
  case 0:
    coord = &x;
    break;
  case 1:
    coord = &y;
    break;
  case 2:
    coord = &z;
    break;
  }

  ++(*coord);

  if (*coord == plane_idx)
    return transformation;
  else
    return glm::mat4(1.0f);
}