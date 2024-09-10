
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
  ~gl_rubics_cube_base_model();

  gl_coloured_cube *cubes[3][3][3];

  void render(GLuint position_attribute_id, GLuint color_attribute_id, GLuint model_matrix_handle);

private:
};