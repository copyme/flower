#version 330 compatibility

layout(location = 0) in vec3 position;
uniform mat4 Projection;
uniform mat4 View;


void main()
{
  gl_Position = Projection * View * vec4(position,1.0);
}
