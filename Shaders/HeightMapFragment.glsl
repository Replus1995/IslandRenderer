#version 330 core

//uniform sampler2D diffuseTex;
//uniform sampler2D bumpTex;

uniform sampler2D grassColor;
uniform sampler2D grassNorm;
uniform sampler2D sandColor;
uniform sampler2D sandNorm;
uniform sampler2D cliffColor;
uniform sampler2D cliffNorm;
uniform sampler2D bottomColor;
uniform sampler2D bottomNorm;

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
    mat3 TBN =  mat3(normalize(IN.tangent), normalize(IN.binormal), normalize(IN.normal));

    float CliffAlpha = clamp(dot(IN.normal,vec3(0, 1, 0))*3-1.8,0,1);

    vec3 grassNormal = texture(grassNorm, IN.texCoord).rgb;
    grassNormal = normalize(TBN * normalize(grassNormal * 2.0 - 1.0));

    vec3 sandNormal = texture(sandNorm, IN.texCoord).rgb;
    sandNormal = normalize(TBN * normalize(sandNormal * 2.0 - 1.0));

    vec3 cliffNormal = texture(cliffNorm, IN.texCoord).rgb;
    cliffNormal = normalize(TBN * normalize(cliffNormal * 2.0 - 1.0));

    vec3 bottomNormal = texture(bottomNorm, IN.texCoord).rgb;
    bottomNormal = normalize(TBN * normalize(bottomNormal * 2.0 - 1.0));

    //fragColour[0] = IN.colour;
    //fragColour[0] = texture(diffuseTex, IN.texCoord);
    //fragColour[1] = vec4(IN.normal, 1.0f);
    //fragColour[1] = vec4(grassNormal.xyz * 0.5 + 0.5, 1.0);
    
    fragColour[0] = vec4(texture(grassColor, IN.texCoord).rgb, 1) * IN.colour.g
                    + vec4(texture(sandColor, IN.texCoord).rgb, 1) * IN.colour.r;
                
    fragColour[1] = vec4(grassNormal * 0.5 + 0.5, 1.0) * IN.colour.g
                    + vec4(sandNormal * 0.5 + 0.5, 1.0) * IN.colour.r;
                    
    /*
    if(IN.colour.g >= IN.colour.r)
    {
        fragColour[1] = vec4(grassNormal.xyz * 0.5 + 0.5, 1.0);
    }
    else
    {
        fragColour[1] = vec4(sandNormal.xyz * 0.5 + 0.5, 1.0);
    }
    */

    fragColour[0] = fragColour[0] * CliffAlpha + texture(cliffColor, IN.texCoord) * ( 1- CliffAlpha);
    fragColour[1] = fragColour[1] * CliffAlpha + vec4(cliffNormal * 0.5 + 0.5, 1.0) * ( 1- CliffAlpha);
    
    float bottomAlpha = clamp(fragColour[0].a, 0, 1);
    
    fragColour[0] = vec4((fragColour[0] * bottomAlpha + texture(bottomColor, IN.texCoord) * (1-bottomAlpha)).rgb, 1.0f);
    fragColour[1] = vec4((fragColour[1] * bottomAlpha + vec4(bottomNormal * 0.5 + 0.5, 1.0) * (1-bottomAlpha)).rgb, 1.0f);
    fragColour[1] = vec4(normalize(fragColour[1].xyz),1.0f);

    
}