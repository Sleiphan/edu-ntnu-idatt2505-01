#include <glm/glm.hpp>

class rubiks_rotation_anim_layer
{
public:
  rubiks_rotation_anim_layer();

  void rotate(char axis, char slice_idx, float angle);

  void apply_transformation(glm::mat4 cubies[3][3][3]);

  glm::mat4 get_transformation(char x, char y, char z);

private:
  /// @brief The transformation matrix of the current animation
  glm::mat4 transformation;

  /// @brief The axis of the current animation
  uint8_t axis;

  /// @brief The plane index of the current animation
  uint8_t plane_idx;
};