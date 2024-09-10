#include "Example_library/gl_coloured_cube.hpp"

int gl_coloured_cube::ref_count = 0;
GLuint gl_coloured_cube::vertex_array_id = -1;
GLuint gl_coloured_cube::vertex_buffer_id = -1;
std::mutex gl_coloured_cube::common_data_mutex;

#define CUBE_SIZE 0.5f

const GLfloat gl_coloured_cube::CUBE_VERTS[] = {
    // Front
    -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE, // 0
    CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,  // 1
    -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,  // 2
    CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,  // 1
    -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,  // 2
    CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,   // 3

    // Left
    -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,  // 0
    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, // 4
    -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,   // 2
    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, // 4
    -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,   // 2
    -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,  // 6

    // Right
    CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,  // 1
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, // 5
    CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,   // 3
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, // 5
    CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,   // 3
    CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,  // 7

    // Up
    -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,  // 2
    CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,   // 3
    -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE, // 6
    CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,   // 3
    -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE, // 6
    CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,  // 7

    // Down
    -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,  // 0
    CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,   // 1
    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, // 4
    CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,   // 1
    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, // 4
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  // 5

    // Back
    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, // 4
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  // 5
    -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,  // 6
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  // 5
    -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,  // 6
    CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE    // 7

};

#undef CUBE_SIZE

void gl_coloured_cube::register_common_static_data()
{
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  glGenBuffers(1, &vertex_buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTS), CUBE_VERTS, GL_STATIC_DRAW);
}

void gl_coloured_cube::unregister_common_static_data()
{
  glDeleteBuffers(1, &vertex_buffer_id);
  glDeleteVertexArrays(1, &vertex_array_id);
}

GLuint gl_coloured_cube::glRegisterCubeColorBuffer(
    glm::vec3 c_front,
    glm::vec3 c_left,
    glm::vec3 c_right,
    glm::vec3 c_up,
    glm::vec3 c_down,
    glm::vec3 c_back)
{
  const GLfloat g_color_buffer_data[] = {
      c_front.x, c_front.y, c_front.z,
      c_front.x, c_front.y, c_front.z,
      c_front.x, c_front.y, c_front.z,
      c_front.x, c_front.y, c_front.z,
      c_front.x, c_front.y, c_front.z,
      c_front.x, c_front.y, c_front.z,

      c_left.x, c_left.y, c_left.z,
      c_left.x, c_left.y, c_left.z,
      c_left.x, c_left.y, c_left.z,
      c_left.x, c_left.y, c_left.z,
      c_left.x, c_left.y, c_left.z,
      c_left.x, c_left.y, c_left.z,

      c_right.x, c_right.y, c_right.z,
      c_right.x, c_right.y, c_right.z,
      c_right.x, c_right.y, c_right.z,
      c_right.x, c_right.y, c_right.z,
      c_right.x, c_right.y, c_right.z,
      c_right.x, c_right.y, c_right.z,

      c_up.x, c_up.y, c_up.z,
      c_up.x, c_up.y, c_up.z,
      c_up.x, c_up.y, c_up.z,
      c_up.x, c_up.y, c_up.z,
      c_up.x, c_up.y, c_up.z,
      c_up.x, c_up.y, c_up.z,

      c_down.x, c_down.y, c_down.z,
      c_down.x, c_down.y, c_down.z,
      c_down.x, c_down.y, c_down.z,
      c_down.x, c_down.y, c_down.z,
      c_down.x, c_down.y, c_down.z,
      c_down.x, c_down.y, c_down.z,

      c_back.x, c_back.y, c_back.z,
      c_back.x, c_back.y, c_back.z,
      c_back.x, c_back.y, c_back.z,
      c_back.x, c_back.y, c_back.z,
      c_back.x, c_back.y, c_back.z,
      c_back.x, c_back.y, c_back.z};

  glBindVertexArray(gl_coloured_cube::vertex_array_id);

  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

  return colorbuffer;
}

void gl_coloured_cube::unregister_color_buffer(const GLuint color_buffer_id)
{
  glBindVertexArray(gl_coloured_cube::vertex_array_id);
  glDeleteBuffers(1, &color_buffer_id);
}
