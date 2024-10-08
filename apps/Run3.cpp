#include "Example_library/rubiks_cube/gl_rubics_cube_base_model.hpp"
#include "Example_library/rubiks_cube/gl_rubiks_cube.hpp"
#include "Example_library/rubiks_cube/rubiks_controller.hpp"
#include "Example_library/shader_loader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <stdio.h>
#include <thread>

#define GL_WINDOW_WIDTH 720
#define GL_WINDOW_HEIGHT 480

void die()
{
  glfwTerminate();
  exit(1);
}

GLFWwindow *create_window()
{
  glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  GLFWwindow *window = glfwCreateWindow(GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT, "Hello OpenGL!", NULL, NULL);

  if (window == NULL)
  {
    fprintf(stderr, "Failed to open GLFW window.\n");
    die();
  }

  return window;
}

GLFWwindow *init_opengl()
{
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    die();
  }

  GLFWwindow *window = create_window();

  if (!window)
    die();

  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental = true;        // Needed in core profile
  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    die();
  }

  return window;
}

int main()
{
  GLFWwindow *window = init_opengl();

  // Load our example shaders
  GLuint shader_id = load_shaders("./shaders/rubiks.vert", "./shaders/rubiks.frag");

  glUseProgram(shader_id);

  glm::vec3 gray = glm::vec3(0.2f);

  gl_rubiks_cube cube(
      glm::vec3(1.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(1.0f, 1.0f, 0.0f),
      glm::vec3(1.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 1.0f, 1.0f),
      gray);

  // Create a handle pointing to the matrix inside our shader
  GLuint local_matrix_handle = glGetUniformLocation(shader_id, "local_matrix");
  GLuint model_matrix_handle = glGetUniformLocation(shader_id, "model_matrix");
  GLuint view_matrix_handle = glGetUniformLocation(shader_id, "view_matrix");
  GLuint projection_matrix_handle = glGetUniformLocation(shader_id, "projection_matrix");
  glm::mat4 local_matrix = glm::mat4(1.0f);
  glm::mat4 model_matrix = glm::mat4(1.0f);
  glm::mat4 view_matrix = glm::lookAt(
      glm::vec3(5, 5, 10),
      glm::vec3(0, 0, 0),
      glm::vec3(0, 1, 0));
  glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)(GL_WINDOW_WIDTH) / (float)(GL_WINDOW_HEIGHT), 0.1f, 100.0f);
  glUniformMatrix4fv(local_matrix_handle, 1, GL_FALSE, &local_matrix[0][0]);
  glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrix[0][0]);
  glUniformMatrix4fv(view_matrix_handle, 1, GL_FALSE, &view_matrix[0][0]);
  glUniformMatrix4fv(projection_matrix_handle, 1, GL_FALSE, &projection_matrix[0][0]);

  glEnable(GL_DEPTH_TEST);

  rubiks_controller cube_ctl(cube);

  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrix[0][0]);
    cube_ctl.process_keypress(window);
    cube_ctl.step();
    cube.render(0, 1, local_matrix_handle);

    glfwSwapBuffers(window); // Update display
    glfwPollEvents();        // Receive events from the window

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
      printf("%d", err);
  }

  return 0;
}