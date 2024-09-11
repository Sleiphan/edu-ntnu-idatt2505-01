

#include "Example_library/gl_coloured_cube.hpp"

gl_coloured_cube::gl_coloured_cube(
    glm::vec3 c_front,
    glm::vec3 c_back,
    glm::vec3 c_up,
    glm::vec3 c_down,
    glm::vec3 c_left,
    glm::vec3 c_right)
{
  gl_coloured_cube::common_data_mutex.lock();
  if (gl_coloured_cube::ref_count <= 0)
  {
    gl_coloured_cube::ref_count = 0;
    gl_coloured_cube::register_common_static_data();
  }

  gl_coloured_cube::ref_count++;
  gl_coloured_cube::common_data_mutex.unlock();

  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
    printf("%d", err);

  this->color_buffer_id = gl_coloured_cube::glRegisterCubeColorBuffer(c_front, c_back, c_up, c_down, c_left, c_right);
}

gl_coloured_cube::~gl_coloured_cube()
{
  gl_coloured_cube::unregister_color_buffer(color_buffer_id);
  this->color_buffer_id = -1;

  gl_coloured_cube::common_data_mutex.lock();
  gl_coloured_cube::ref_count--;

  if (gl_coloured_cube::ref_count <= 0)
    gl_coloured_cube::unregister_common_static_data();
  gl_coloured_cube::common_data_mutex.unlock();
}

void gl_coloured_cube::render(const GLuint position_attribute_id, const GLuint color_attribute_id) const
{
  glBindVertexArray(gl_coloured_cube::vertex_array_id);

  glEnableVertexAttribArray(position_attribute_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_coloured_cube::vertex_buffer_id);
  glVertexAttribPointer(position_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glEnableVertexAttribArray(color_attribute_id);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
  glVertexAttribPointer(color_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);

  glDisableVertexAttribArray(color_attribute_id);
  glDisableVertexAttribArray(position_attribute_id);
}

#undef GLM_SWIZZLE