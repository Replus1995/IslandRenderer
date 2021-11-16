#version 330 core

uniform sampler2D diffuseTex;
uniform samplerCube CubeTex;

uniform vec3 cameraPos;

in Vertex
{
    vec2 texCoord;
    vec3 normal;
    vec3 worldPos;
} IN;

out vec4 fragColour;

void main(void)
{
    vec3 viewDir = normalize(cameraPos - IN.worldPos);
    vec4 diffuse = texture(diffuseTex, IN.texCoord);

    vec3 reflectDir = reflect(-viewDir,normalize(IN.normal));
    vec4 reflectTex = texture(CubeTex,reflectDir);

    fragColour = reflectTex + (diffuse * 0.25f);
}