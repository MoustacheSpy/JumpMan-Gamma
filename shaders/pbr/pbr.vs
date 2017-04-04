#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoords;
layout (location = 2) in vec3 normals;
out vec2 TexCoords;
out vec3 Normal;
out vec3 WorldPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 pos;
void main()
{

	pos=gl_Position = projection*model*view*vec4(position,1.0f);
	TexCoords=vec2(texcoords.xy);
	Normal = mat3(transpose(inverse(model))) * normals;  
	WorldPos = vec3(model * vec4(position, 1.0f));
};