#version 330 core

uniform sampler2D diffuseTex;
uniform sampler2D normTex;

uniform vec3 cameraPos;

uniform vec3 lightDir;
uniform vec4 lightColour;
uniform float lightStrength;

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

out vec4 fragColour;

void main(void)
{
    mat3 TBN =  mat3(normalize(IN.tangent), normalize(IN.binormal), normalize(IN.normal));

    vec4 diffuse = texture(diffuseTex, IN.texCoord);
    vec3 normal = texture(normTex, IN.texCoord).rgb;
    normal = normalize(TBN * normalize(normal * 2.0 - 1.0));


    vec3 incident = normalize(lightDir * -1.0f);
    vec3 viewDir = normalize(cameraPos - IN.worldPos);
    vec3 halfDir = normalize(incident + viewDir);

    float lambert = clamp(dot(incident, normal), 0.0, 1.0);
    float specFactor = clamp(dot(halfDir, normal), 0.0, 1.0);
    specFactor = pow(specFactor, 60.0);
    vec3 surface = (diffuse.rgb * lightColour.rgb);
    fragColour.rgb = surface * lambert * lightStrength;
    fragColour.rgb += (lightColour.rgb * specFactor) * lightStrength * 0.33;
    fragColour.rgb += surface * 0.1f;
    fragColour.rgb = vec3(1,1,1);
    fragColour.a = 1.0f;

}