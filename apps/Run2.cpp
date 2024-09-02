#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Example_library/shader_loader.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

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

int main()
{
  GLFWwindow *window = init_opengl();

  // Load our example shaders
  GLuint shader_id = load_shaders("./shaders/shapes.vert", "./shaders/shapes.frag");
  glUseProgram(shader_id);

  // Create a handle pointing to the matrix inside our shader
  GLuint matrix_handle = glGetUniformLocation(shader_id, "MVP");
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)(GL_WINDOW_WIDTH) / (float)(GL_WINDOW_HEIGHT), 0.1f, 100.0f);

  // Camera matrix
  glm::mat4 View = glm::lookAt(
      glm::vec3(0, 0, 5),
      glm::vec3(0, 0, 0),
      glm::vec3(0, 1, 0));

  // Model matrix: an identity matrix (model will be at the origin)
  glm::mat4 Model = glm::mat4(1.0f);
  // Our ModelViewProjection: multiplication of our 3 matrices
  glm::mat4 final_matrix = Projection * View * Model;
  glUniformMatrix4fv(matrix_handle, 1, GL_FALSE, &final_matrix[0][0]);

  // Setup one Vertex Array Object to contain multiple Vertex Buffer Objects
  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);

  glBindVertexArray(vertex_array);
  GLuint vertices_vbo;
  glGenBuffers(1, &vertices_vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);                                                   // Select our vertex buffer; we are going to do something with it.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data_source), vertex_data_source, GL_STATIC_DRAW); // Add data to VBO

  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0)
  {
    glEnableVertexAttribArray(0); // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
    // render(0, GL_POINTS, 8);
    // render(0, GL_LINES, 8);
    // render(0, GL_LINE_STRIP, 8);
    render(0, GL_LINE_LOOP, 8);
    // render(0, GL_TRIANGLES, 6);
    // render(0, GL_TRIANGLE_STRIP, 8);
    // render(0, GL_TRIANGLE_FAN, 8);
    // render(0, GL_QUADS, 4);        // GL_INVALID_ENUM
    // render(0, GL_QUAD_STRIP, 4);   // GL_INVALID_ENUM
    // render(0, GL_POLYGON, 8);      // GL_INVALID_ENUM
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window); // Update display
    glfwPollEvents();        // Receive events from the window

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 10));

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
      printf("%d", err);
  }

  return 0;
}