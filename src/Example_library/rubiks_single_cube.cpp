#define GLM_FORCE_SWIZZLE

#include "Example_library/rubiks_cube.hpp"
#include <glm/ext/matrix_transform.hpp>

glm::mat4 rubiks_single_cube::set_position(const glm::vec3 &position)
{
  this->position = position;
  return recalc_render_matrix();
}

glm::mat4 rubiks_single_cube::set_rotation(const GLfloat &angle, const glm::vec3 &axis)
{
  this->rotation = glm::vec4(axis, angle);
  return recalc_render_matrix();
}

glm::mat4 rubiks_single_cube::recalc_render_matrix()
{
  this->matrix = glm::rotate(glm::mat4(1.0f), this->rotation.w, this->rotation.xyz());
  this->matrix = glm::translate(this->matrix, this->position);
  return this->matrix;
}