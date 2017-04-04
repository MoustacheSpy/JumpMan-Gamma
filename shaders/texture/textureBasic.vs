#version 330 core
layout (location = 0) in vec3 position;
layout (location =1) in vec3 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;
out vec4 pos;
out vec3 ourColor;
void main()
{
    pos=gl_Position =projection * view * model * position ;
    TexCoord = vec2(texCoord.x, texCoord.y);
	
}