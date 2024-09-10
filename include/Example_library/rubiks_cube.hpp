#ifndef CUSTOM_RUBIKS_CUBE
#define CUSTOM_RUBIKS_CUBE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <mutex>

class rubiks_cube
{
public:
  void rotate();

  void reset_matrices();

private:
  glm::mat4 mats[3][3][3];

  glm::mat4 &master_matrix() { return mats[1][1][1]; }

  static const float CUBE_VERTS[];
  static const int CUBE_VERT_INDICES[];
  static const float CUBE_CORNER_COLORS[];
};

class rubiks_single_cube
{
public:
  glm::mat4 get_render_matrix() { return matrix; };

  glm::mat4 set_position(const glm::vec3 &position);
  glm::mat4 set_rotation(const GLfloat &angle, const glm::vec3 &axis);

private:
  glm::mat4 matrix;
  glm::vec3 position;
  glm::vec4 rotation;

  glm::mat4 recalc_render_matrix();
};

#endif