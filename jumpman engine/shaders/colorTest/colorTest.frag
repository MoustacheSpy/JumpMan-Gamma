#version 330 core
out vec4 color;
in vec3 ourColor;
in vec4 pos;
vec3 tempCol;

void main()
{
	tempCol.x = ourColor.x +0.5;
	tempCol.yz = ourColor.yz +0.1;
    color = vec4(1.0f,1.0f,1.0f, 1.0f);
};