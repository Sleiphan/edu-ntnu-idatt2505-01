#ifndef CUSTOM_GL_RUBIKS_CUBE
#define CUSTOM_GL_RUBIKS_CUBE

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

void gl_rubiks_cube::render(GLuint position_attribute_id, GLuint color_attribute_id, GLuint model_matrix_handle)
{
    for (char z = -1; z < 2; ++z)
        for (char y = -1; y < 2; ++y)
            for (char x = -1; x < 2; ++x)
            {
                rubiks_cubie cube = matrix_model.get_cubie(x, y, z);
                const gl_coloured_cube &model = base_model.get_cubie(cube.opos);

                glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &cube.m[0][0]);
                model.render(position_attribute_id, color_attribute_id);
            }
}

void gl_rubiks_cube::rotate(char axis, char slice_idx, bool counterclockwise)
{
    matrix_model.rotate(axis, slice_idx, counterclockwise);
}

#endif // CUSTOM_GL_RUBIKS_CUBE