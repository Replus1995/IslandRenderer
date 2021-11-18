#version 330 core

in Vertex
{
    vec4 colour;
    vec2 texCoord;
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
    vec3 worldPos;
} IN;

out vec4 fragColour[2];

void main(void)
{
    fragColour[0] = vec4(1,1,1,1);
    fragColour[1] = vec4(IN.normal * 0.5 + 0.5, 1.0);
}