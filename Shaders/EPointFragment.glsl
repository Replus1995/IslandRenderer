#version 330 core

uniform vec4 baseColour;
uniform vec3 emissiveColour;
uniform sampler2D colourTex;

in Vertex
{
    vec4 colour;
    vec2 texCoord;
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
    vec3 worldPos;
} IN;

out vec4 fragColour[4];

void main(void)
{
    vec4 texColour = texture(colourTex, IN.texCoord);
    //fragColour[0] = vec4(baseColour.rgb, texColour.a);
    fragColour[0] = vec4(0,0,0,texColour.a);
    float normalAlpha = 0.0;
    if(texColour.r > 0)
    {
        normalAlpha = 1.0;
    }
    fragColour[1] = vec4(IN.normal, 1);//vec4(IN.normal * 0.5 + 0.5, normalAlpha);
    fragColour[2] = vec4(emissiveColour, 1.0);
}