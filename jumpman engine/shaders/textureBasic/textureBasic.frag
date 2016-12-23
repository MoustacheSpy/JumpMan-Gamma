#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec4 pos;
out vec4 color;

//uniform sampler2D ourTexture;
void main()
{
	vec3 tempCol;
	
	tempCol.xyz = ourColor.xyz +pos.xyz;
	//*vec4(tempCol,1.0);
	color =  pos;

}