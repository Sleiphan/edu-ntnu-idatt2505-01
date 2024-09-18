#ifndef CUSTOM_RUBIKS_CONTROLLER
#define CUSTOM_RUBIKS_CONTROLLER

#include "Example_library/rubiks_cube/gl_rubiks_cube.hpp"
#include <GLFW/glfw3.h>
#include <chrono>

class rubiks_controller
{
public:
  rubiks_controller(gl_rubiks_cube &control_object);

  void process_keypress(GLFWwindow *window);

  void initiate_anim(char axis, char slice_idx, bool counterclockwise);

  void step();

private:
  gl_rubiks_cube &cube;

  float current_rotation;
  char current_axis;
  char current_slice;
  bool current_counterclockwise;

  float angle_speed;
  std::chrono::high_resolution_clock::time_point last_step;
};

#endif // CUSTOM_RUBIKS_CONTROLLER