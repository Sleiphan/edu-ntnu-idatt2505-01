
#include "Example_library/rubiks_cube/gl_rubics_cube_base_model.hpp"
#include "Example_library/rubiks_cube/rubiks_cube.hpp"

class gl_rubiks_cube
{
public:
  gl_rubiks_cube(
      glm::vec3 c_front,
      glm::vec3 c_back,
      glm::vec3 c_up,
      glm::vec3 c_down,
      glm::vec3 c_left,
      glm::vec3 c_right,
      glm::vec3 c_empty);

  void render(GLuint position_attribute_id, GLuint color_attribute_id, GLuint model_matrix_handle);

private:
  rubiks_cube matrix_model;
  gl_rubics_cube_base_model base_model;
};