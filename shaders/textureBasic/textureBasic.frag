#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec4 pos;
out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	color =  texture(ourTexture,TexCoord);
}