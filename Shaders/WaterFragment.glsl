#version 330 core

uniform sampler2D diffuseTex;
uniform sampler2D normTex;

//uniform samplerCube CubeTex;
//uniform vec3 cameraPos;

in Vertex
{
    vec2 texCoord;
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
    vec3 worldPos;
} IN;

//out vec4 fragColour;
out vec4 fragColour[3];

void main(void)
{
    mat3 TBN =  mat3(normalize(IN.tangent), normalize(IN.binormal), normalize(IN.normal));

    vec4 diffuse = texture(diffuseTex, IN.texCoord);
    vec3 normal = texture(normTex, IN.texCoord).rgb;
    normal = normalize(TBN * normalize(normal * 2.0 - 1.0));

    fragColour[0] = vec4(diffuse.rgb, 0.3f);
    //fragColour[0] = vec4(1,1,1,1);
    fragColour[1] = vec4(normal * 0.5 + 0.5, 1.0f);

    //vec3 viewDir = normalize(cameraPos - IN.worldPos);
    //vec3 reflectDir = reflect(-viewDir,normalize(IN.normal));
    //vec4 reflectTex = texture(CubeTex,reflectDir);
    //fragColour = reflectTex + (diffuse * 0.25f);

    fragColour[2] = vec4(0,0,0,1);
}