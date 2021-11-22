#version 330 core

uniform samplerCube cubeTex;
uniform sampler2D sceneTex;

in Vertex
{
    vec2 texCoord;
    vec3 viewDir;
} IN;

out vec4 fragColour;

void main(void)
{
    float alpha = 1.0;
    if(texture(sceneTex, IN.texCoord).a < 0.1)
    {
        alpha = 0.0;
    }
    fragColour = vec4(texture(cubeTex, normalize(IN.viewDir)).rgb, 1.0f - alpha);
}