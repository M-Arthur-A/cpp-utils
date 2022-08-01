#version 430 core
layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec3 a_color;

out vec3 color;

void main() {
  gl_Position = vec4( a_pos, 0.0, 1.0 );
  color = a_color;
}
