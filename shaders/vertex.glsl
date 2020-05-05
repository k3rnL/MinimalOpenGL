#version 140

in vec3 point;
out vec2 UV;

void main()
{
  gl_Position = vec4(point, 1);
  UV = point.xy;
}