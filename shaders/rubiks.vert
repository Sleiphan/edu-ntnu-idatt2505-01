#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;

out vec3 fragment_color;

uniform mat4 local_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
  gl_Position = projection_matrix * view_matrix * model_matrix * local_matrix * vec4(vertex_position, 1);

  fragment_color = vertex_color;
}