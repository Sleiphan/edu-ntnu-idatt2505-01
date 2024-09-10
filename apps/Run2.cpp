#include <Example_library/shader_loader.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
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

static const float vertex_data_source[] = {
    0.0, 2.0, 0.0,
    1.5, 1.5, 0.0,
    2.0, 0.0, 0.0,
    1.5, -1.5, 0.0,
    0.0, -2.0, 0.0,
    -1.5, -1.5, 0.0,
    -2.0, 0.0, 0.0,
    -1.5, 1.5, 0.0};

void render(int attrib_ID, GLenum mode, GLint vertex_count)
{
  glVertexAttribPointer(
      attrib_ID, // attribute 0. No particular reason for 0, but must match the layout in the shader.
      3,         // size
      GL_FLOAT,  // type
      GL_FALSE,  // normalized?
      0,         // stride
      (void *)0  // array buffer offset
  );
  glDrawArrays(mode, 0, vertex_count);
}

glm::mat4 create_model_matrix(glm::vec3 position, glm::vec3 scale)
{
  glm::mat4 model = glm::mat4(1.0f);

  model[3][0] += position.x;
  model[3][1] += position.y;
  model[3][2] += position.z;

  model[0][0] *= scale.x;
  model[1][1] *= scale.y;
  model[2][2] *= scale.z;

  return model;
}

int main()
{
  GLFWwindow *window = init_opengl();

  // Load our example shaders
  GLuint shader_id = load_shaders("./shaders/shapes.vert", "./shaders/shapes.frag");
  glUseProgram(shader_id);

  // Create a handle pointing to the matrix inside our shader
  GLuint model_matrix_handle = glGetUniformLocation(shader_id, "model_matrix");
  GLuint view_matrix_handle = glGetUniformLocation(shader_id, "view_matrix");
  GLuint projection_matrix_handle = glGetUniformLocation(shader_id, "projection_matrix");
  // glm::mat4 Model = glm::mat4(1.0f);
  glm::mat4 view_matrix = glm::lookAt(
      glm::vec3(0, 0, 20),
      glm::vec3(0, 0, 0),
      glm::vec3(0, 1, 0));
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)(GL_WINDOW_WIDTH) / (float)(GL_WINDOW_HEIGHT), 0.1f, 100.0f);
  // glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &Model[0][0]);
  glUniformMatrix4fv(view_matrix_handle, 1, GL_FALSE, &view_matrix[0][0]);
  glUniformMatrix4fv(projection_matrix_handle, 1, GL_FALSE, &Projection[0][0]);

  float space = 5;
  float scale = 0.5;

  glm::mat4 model_matrices[] = {
      create_model_matrix(glm::vec3(-space, space, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(0, space, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(space, space, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(-space, 0, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(0, 0, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(space, 0, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(-space, -space, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(0, -space, 0), glm::vec3(scale)),
      create_model_matrix(glm::vec3(space, -space, 0), glm::vec3(scale)),
  };

  // Setup one Vertex Array Object to contain multiple Vertex Buffer Objects
  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);

  glBindVertexArray(vertex_array);
  GLuint vertices_vbo;
  glGenBuffers(1, &vertices_vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);                                                   // Select our vertex buffer; we are going to do something with it.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data_source), vertex_data_source, GL_STATIC_DRAW); // Add data to VBO

  float current_rotation = 0.0f;

  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
    glm::mat4 view = glm::rotate(view_matrix, current_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(view_matrix_handle, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrices[0][0][0]);
    render(0, GL_POINTS, 8);
    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrices[1][0][0]);
    render(0, GL_LINES, 8);
    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrices[2][0][0]);
    render(0, GL_LINE_STRIP, 8);
    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrices[3][0][0]);
    render(0, GL_LINE_LOOP, 8);
    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrices[4][0][0]);
    render(0, GL_TRIANGLES, 6);
    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrices[5][0][0]);
    render(0, GL_TRIANGLE_STRIP, 8);
    glUniformMatrix4fv(model_matrix_handle, 1, GL_FALSE, &model_matrices[6][0][0]);
    render(0, GL_TRIANGLE_FAN, 8);
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window); // Update display
    glfwPollEvents();        // Receive events from the window

    current_rotation += 0.025f;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
      printf("%d", err);
  }

  return 0;
}