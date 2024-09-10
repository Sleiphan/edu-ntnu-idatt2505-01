
#include "Example_library/rubiks_cube/gl_rubics_cube_base_model.hpp"
#include <glm/ext/matrix_transform.hpp>

gl_rubics_cube_base_model::gl_rubics_cube_base_model(
    glm::vec3 c_front,
    glm::vec3 c__back,
    glm::vec3 c____up,
    glm::vec3 c__down,
    glm::vec3 c__left,
    glm::vec3 c_right,
    glm::vec3 c_empty)
{
  cubes[0][0][0] = new gl_coloured_cube(c_empty, c__back, c_empty, c__down, c__left, c_empty); // Back, down,  left
  cubes[0][0][1] = new gl_coloured_cube(c_empty, c__back, c_empty, c__down, c_empty, c_empty); // Back, down,  mid
  cubes[0][0][2] = new gl_coloured_cube(c_empty, c__back, c_empty, c__down, c_empty, c_right); // Back, down,  right
  cubes[0][1][0] = new gl_coloured_cube(c_empty, c__back, c_empty, c_empty, c__left, c_empty); // Back, level, left
  cubes[0][1][1] = new gl_coloured_cube(c_empty, c__back, c_empty, c_empty, c_empty, c_empty); // Back, level, mid
  cubes[0][1][2] = new gl_coloured_cube(c_empty, c__back, c_empty, c_empty, c_empty, c_right); // Back, level, right
  cubes[0][2][0] = new gl_coloured_cube(c_empty, c__back, c____up, c_empty, c__left, c_empty); // Back, up,    left
  cubes[0][2][1] = new gl_coloured_cube(c_empty, c__back, c____up, c_empty, c_empty, c_empty); // Back, up,    mid
  cubes[0][2][2] = new gl_coloured_cube(c_empty, c__back, c____up, c_empty, c_empty, c_right); // Back, up,    right

  cubes[1][0][0] = new gl_coloured_cube(c_empty, c_empty, c_empty, c__down, c__left, c_empty); // Between, down,  left
  cubes[1][0][1] = new gl_coloured_cube(c_empty, c_empty, c_empty, c__down, c_empty, c_empty); // Between, down,  mid
  cubes[1][0][2] = new gl_coloured_cube(c_empty, c_empty, c_empty, c__down, c_empty, c_right); // Between, down,  right
  cubes[1][1][0] = new gl_coloured_cube(c_empty, c_empty, c_empty, c_empty, c__left, c_empty); // Between, level, left
  cubes[1][1][1] = new gl_coloured_cube(c_empty, c_empty, c_empty, c_empty, c_empty, c_empty); // Between, level, mid
  cubes[1][1][2] = new gl_coloured_cube(c_empty, c_empty, c_empty, c_empty, c_empty, c_right); // Between, level, right
  cubes[1][2][0] = new gl_coloured_cube(c_empty, c_empty, c____up, c_empty, c__left, c_empty); // Between, up,    left
  cubes[1][2][1] = new gl_coloured_cube(c_empty, c_empty, c____up, c_empty, c_empty, c_empty); // Between, up,    mid
  cubes[1][2][2] = new gl_coloured_cube(c_empty, c_empty, c____up, c_empty, c_empty, c_right); // Between, up,    right

  cubes[2][0][0] = new gl_coloured_cube(c_front, c_empty, c_empty, c__down, c__left, c_empty); // Front, down,  left
  cubes[2][0][1] = new gl_coloured_cube(c_front, c_empty, c_empty, c__down, c_empty, c_empty); // Front, down,  mid
  cubes[2][0][2] = new gl_coloured_cube(c_front, c_empty, c_empty, c__down, c_empty, c_right); // Front, down,  right
  cubes[2][1][0] = new gl_coloured_cube(c_front, c_empty, c_empty, c_empty, c__left, c_empty); // Front, level, left
  cubes[2][1][1] = new gl_coloured_cube(c_front, c_empty, c_empty, c_empty, c_empty, c_empty); // Front, level, mid
  cubes[2][1][2] = new gl_coloured_cube(c_front, c_empty, c_empty, c_empty, c_empty, c_right); // Front, level, right
  cubes[2][2][0] = new gl_coloured_cube(c_front, c_empty, c____up, c_empty, c__left, c_empty); // Front, up,    left
  cubes[2][2][1] = new gl_coloured_cube(c_front, c_empty, c____up, c_empty, c_empty, c_empty); // Front, up,    mid
  cubes[2][2][2] = new gl_coloured_cube(c_front, c_empty, c____up, c_empty, c_empty, c_right); // Front, up,    right
}

gl_rubics_cube_base_model::~gl_rubics_cube_base_model()
{
  for (int z = 0; z < 3; ++z)
    for (int y = 0; y < 3; ++y)
      for (int x = 0; x < 3; ++x)
        delete cubes[z][y][x];
}

void gl_rubics_cube_base_model::render(GLuint position_attribute_id, GLuint color_attribute_id, GLuint model_matrix_handle)
{
  for (int z = 0; z < 3; ++z)
    for (int y = 0; y < 3; ++y)
      for (int x = 0; x < 3; ++x)
      {
        glm::mat4 model_matrix = glm::mat4(1.0f);
        model_matrix = glm::scale(model_matrix, glm::vec3(1.0f / 2.5));
        glm::vec3 pos = glm::vec3(x - 1.0f, y - 1.0f, z - 1.0f);
        model_matrix = glm::translate(model_matrix, pos);
        model_matrix = glm::scale(model_matrix, glm::vec3(0.8f));
        glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrix[0][0]);

        cubes[z][y][x]->render(position_attribute_id, color_attribute_id);
      }
}