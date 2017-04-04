#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texcoords;
out vec2 texCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 pos;
void main()
{
	pos=gl_Position = projection*view*model*vec4(position,1.0f);
	texCoords=vec2(texcoords.xy);
	mat3 normalMatrix = mat3(transpose(inverse(view * model)));
};