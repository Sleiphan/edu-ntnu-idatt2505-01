
#include "Example_library/rubiks_cube/gl_rubiks_cube.hpp"

gl_rubiks_cube::gl_rubiks_cube(
    glm::vec3 c_front,
    glm::vec3 c_back,
    glm::vec3 c_up,
    glm::vec3 c_down,
    glm::vec3 c_left,
    glm::vec3 c_right,
    glm::vec3 c_empty)
    : base_model(c_front, c_back, c_up, c_down, c_left, c_right, c_empty)
{
}