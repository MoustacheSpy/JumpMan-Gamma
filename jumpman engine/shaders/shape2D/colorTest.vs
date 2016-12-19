#version 330 core
layout (location = 0) in vec3 position;

uniform float factor;
out vec3 ourColor; // Output a color to the fragment shader
out vec4 pos; 
uniform mat4 trasform;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
void main()
{
	pos = gl_Position = transform*vec4(position.x -factor, position.y, position.z, 1.0);
	ourColor = vec3(position.x -factor, position.y, position.z);
};