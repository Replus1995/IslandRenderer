#version 330 core

uniform vec4 baseColour;
uniform vec3 emissiveColour;

in Vertex
{
    vec4 colour;
    vec2 texCoord;
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
    vec3 worldPos;
} IN;

out vec4 fragColour[3];

void main(void)
{
    fragColour[0] = baseColour;
    fragColour[1] = vec4(IN.normal * 0.5 + 0.5, 1.0);
    fragColour[2] = vec4(emissiveColour, 1.0);
}