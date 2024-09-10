#ifndef CUSTOM_GL_COLOURED_CUBE
#define CUSTOM_GL_COLOURED_CUBE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <mutex>

class gl_coloured_cube
{
public:
  gl_coloured_cube(
      glm::vec3 c_front,
      glm::vec3 c_back,
      glm::vec3 c_up,
      glm::vec3 c_down,
      glm::vec3 c_left,
      glm::vec3 c_right);
  ~gl_coloured_cube();

  void render(GLuint position_attribute_id, GLuint color_attribute_id);

private:
  GLuint color_buffer_id;

  static int ref_count;
  static std::mutex common_data_mutex;

  static GLuint vertex_array_id;
  static GLuint vertex_buffer_id;
  static const GLfloat CUBE_VERTS[];

  static void register_common_static_data();
  static void unregister_common_static_data();

  static GLuint glRegisterCubeColorBuffer(
      glm::vec3 c_front,
      glm::vec3 c_back,
      glm::vec3 c_up,
      glm::vec3 c_down,
      glm::vec3 c_left,
      glm::vec3 c_right);

  void unregister_color_buffer(const GLuint color_buffer_id);
};

#endif