#include "Example_library/rubiks_cube/rubiks_controller.hpp"
#include <glm/ext/scalar_constants.hpp>

rubiks_controller::rubiks_controller(gl_rubiks_cube &control_object) : cube(control_object),
                                                                       current_rotation(0.0f),
                                                                       current_axis(-1),
                                                                       current_slice(-1),
                                                                       angle_speed(glm::pi<float>() / 2)
{
}

void rubiks_controller::process_keypress(GLFWwindow *window)
{
  static const int keys[] = {
      GLFW_KEY_1,
      GLFW_KEY_2,
      GLFW_KEY_3,
      GLFW_KEY_Q,
      GLFW_KEY_W,
      GLFW_KEY_E,
      GLFW_KEY_A,
      GLFW_KEY_S,
      GLFW_KEY_D};

  if (current_axis != -1)
    return;

  char key = -1;
  for (int i = 0; i < 9; ++i)
    if (glfwGetKey(window, keys[i]))
    {
      key = i;
      break;
    }

  if (key == -1)
    return;

  char axis = key / 3;
  char idx = key % 3;
  bool counterclockwise = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);

  initiate_anim(axis, idx, counterclockwise);
}

void rubiks_controller::initiate_anim(char axis, char slice_idx, bool counterclockwise)
{
  current_rotation = 0.0f;
  current_axis = axis;
  current_slice = slice_idx;
  current_counterclockwise = counterclockwise;
  last_step = std::chrono::high_resolution_clock::now();
}

void rubiks_controller::step()
{
  if (current_axis == -1)
    return;

  float delta = (std::chrono::high_resolution_clock::now() - last_step).count() / 1.0E9F;
  last_step = std::chrono::high_resolution_clock::now();

  if (abs(current_rotation) < glm::pi<float>() / 2)
  {
    cube.rotate_anim(current_axis, current_slice, current_rotation);
    float angle_amount = angle_speed * delta;
    angle_amount *= current_counterclockwise ? 1 : -1;
    current_rotation += angle_amount;
  }
  else
  {
    cube.rotate_anim(current_axis, current_slice, 0);
    cube.rotate(current_axis, current_slice, current_counterclockwise);
    current_rotation = 0.0f;
    current_axis = -1;
    current_slice = -1;
    current_counterclockwise = false;
  }
}
