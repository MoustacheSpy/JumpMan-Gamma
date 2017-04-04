#version 330 core
out vec4 color;
in vec2 texCoords;
in vec4 pos;
uniform sampler2D ourTexture;
uniform vec4 mixCol;

void main()
{
    vec4 texColor = texture(ourTexture, texCoords*-1);
    //if(texColor.a < 0.1f)
     //	 discard;ss
ss
	
    color = vec4(1.0f,1.0f,1.0f,1.0f);
};