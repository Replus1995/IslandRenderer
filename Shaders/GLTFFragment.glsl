#version 330 core

uniform vec4 baseColor;
uniform sampler2D baseColorTex;
uniform float metallic;
uniform float roughness;
uniform sampler2D metallicRoughnessTex;
uniform sampler2D normalTex;
uniform float normalScale;
uniform sampler2D occlutionTex;
uniform float occlutionStrength;
uniform sampler2D emissiveTex;
uniform vec3 emissiveFactor;
uniform int alphaMode;
uniform float alphaCutoff;
//uniform bool doubleSided;

uniform bool bUseBaseColorTex;
uniform bool bUseMetallicRoughnessTex;
uniform bool bUseNormalTex;
uniform bool bUseOcclutionTex;
uniform bool bUseEmissiveTex;

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
   
    if(bUseBaseColorTex)
    {
        fragColour[0] = texture(baseColorTex, IN.texCoord) * baseColor;
    }
    else
    {
        fragColour[0] = IN.colour * baseColor;
    }

    if(alphaMode == 0)
    {
        fragColour[0].a = 1.0f;
    }
    else if(alphaMode == 1)
    {
        fragColour[0].a = fragColour[0].a >= alphaCutoff ? 1.0f : 0.0f;
    }

    if(bUseNormalTex)
    {
        mat3 TBN =  mat3(normalize(IN.tangent), normalize(IN.binormal), normalize(IN.normal));
        vec3 localNormal = texture(normalTex, IN.texCoord).rgb;
        localNormal = normalize((localNormal * 2.0 - 1.0) * vec3(normalScale, normalScale, 1.0f));
        fragColour[1] = vec4(normalize(TBN * localNormal), 1.0f);
    }
    else
    {
        fragColour[1] = vec4(IN.normal, 1.0f);
    }

    
}