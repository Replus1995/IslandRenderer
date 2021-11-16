#version 330 core

uniform sampler2D diffuseTex;
uniform sampler2D bumpTex;
uniform sampler2D shadowTex;

uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;
uniform vec3 cameraPos;

in Vertex
{
    vec3 colour;
    vec2 texCoord;
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
    vec3 worldPos;
    vec4 shadowProj;
} IN;

out vec4 fragColour;

void main(void)
{
    vec3 incident =  normalize(lightPos - IN.worldPos);
    vec3 viewDir = normalize(cameraPos - IN.worldPos);
    vec3 halfDir = normalize(incident + viewDir);

    mat3 TBN =  mat3(normalize(IN.tangent), normalize(IN.binormal), normalize(IN.normal));
    
    vec4 diffuse = texture(diffuseTex, IN.texCoord);
    vec3 bumpNormal = texture(bumpTex, IN.texCoord).rgb;
    bumpNormal = normalize(TBN * normalize(bumpNormal * 2.0 - 1.0));

    float lambert = max(dot(incident, bumpNormal), 0.0f);
    float distance = length(lightPos - IN.worldPos);
    float attenuation = 1.0 - clamp(distance / lightRadius, 0.0f, 1.0f);
    float specFactor = clamp(dot(halfDir, bumpNormal), 0.0f, 1.0f);
    specFactor = pow(specFactor, 60.0);

    float shadow = 1.0;
    vec3 shadowNDC = IN.shadowProj.xyz / IN.shadowProj.w;
    if( abs(shadowNDC.x) < 1.0f &&
        abs(shadowNDC.y) < 1.0f &&
        abs(shadowNDC.z) < 1.0f)
        {
            vec3 biasCoord = shadowNDC * 0.5f + 0.5f;
            float shadowZ = texture(shadowTex,biasCoord.xy).x;
            if(shadowZ < biasCoord.z)
            {
                shadow = 0.0f;
            }
        }


    vec3 surface = (diffuse.rgb * lightColour.rgb);
    fragColour.rgb = surface * lambert * attenuation;
    fragColour.rgb += (lightColour.rgb * specFactor) * attenuation * 0.33;
    fragColour.rgb *= shadow;
    fragColour.rgb += surface *0.1f;
    fragColour.a = diffuse.a;
}