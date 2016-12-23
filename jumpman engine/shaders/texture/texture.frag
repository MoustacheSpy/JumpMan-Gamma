#version 330 core
out vec4 color;
in vec4 pos;
in vec2 texCoords;
uniform sampler2D ourTexture;
uniform vec4 mixCol;
vec3 tempCol;

void main()
{
    vec4 texColor = texture(ourTexture, texCoords);
    if(texColor.a < 0.1)
        discard;
    
	color = mix(texColor,pos,0.5);
};