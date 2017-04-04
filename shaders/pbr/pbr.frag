
#version 330 core
out vec4 FragColor;
out vec4 color;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform sampler2D mytexture;
const float offset = 1.0 / 300;  
  
void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );
float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16 
   );
    //if(texture(mytexture,TexCoords).a < 0.1)
  	//discard;
    vec3 lightColor = vec3(1.0,1.0,1.0);
    vec3 lightPos = vec3(2.4,2.0,2.0);
    vec3 objectColor = texture(mytexture,TexCoords).rgb;
    // Ambient
    float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
	 vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(mytexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    vec3 result = (ambient + diffuse) * col;
    color = vec4(texture(mytexture,TexCoords.).a,0.0,0.0,1.0);
    
}  
