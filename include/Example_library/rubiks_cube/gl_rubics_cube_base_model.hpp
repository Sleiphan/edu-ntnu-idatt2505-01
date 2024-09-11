#ifndef CUSTOM_GL_RUBIKS_CUBE_BASE_MODEL
#define CUSTOM_GL_RUBIKS_CUBE_BASE_MODEL

#include "Example_library/gl_coloured_cube.hpp"

class gl_rubics_cube_base_model
{
public:
  gl_rubics_cube_base_model(
      glm::vec3 c_front,
      glm::vec3 c_back,
      glm::vec3 c_up,
      glm::vec3 c_down,
      glm::vec3 c_left,
      glm::vec3 c_right,
      glm::vec3 c_empty);

  gl_coloured_cube cubies[3][3][3];

  const gl_coloured_cube &get_cubie(char x, char y, char z) { return cubies[z + 1][y + 1][x + 1]; }
  const gl_coloured_cube &get_cubie(glm::i8vec3 pos) { return cubies[pos.z + 1][pos.y + 1][pos.x + 1]; }

  void render(GLuint position_attribute_id, GLuint color_attribute_id, GLuint model_matrix_handle);

private:
};

#endif // CUSTOM_GL_RUBIKS_CUBE_BASE_MODEL