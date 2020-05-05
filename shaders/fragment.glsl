#version 140

in vec2 UV;
out vec3 fragColor;

void main()
{
  fragColor = vec3(UV, 1);
}