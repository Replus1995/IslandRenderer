#version 330 core

uniform sampler2D depthTex;
uniform sampler2D normTex;
uniform sampler2D shadowTex;

uniform vec2 pixelSize;
uniform vec3 cameraPos;

uniform vec3 lightDir;
uniform vec4 lightColour;
uniform float lightStrength;

uniform mat4 inverseProjView;
uniform mat4 shadowMatrix;

out vec4 diffuseOutput;
out vec4 specularOutput;

void main(void)
{
    vec2 texCoord = vec2(gl_FragCoord.xy * pixelSize);
    float depth = texture(depthTex, texCoord).r;
    vec3 ndcPos = vec3(texCoord, depth) * 2.0 - 1.0;
    vec4 invClipPos = inverseProjView * vec4(ndcPos, 1.0);
    vec3 worldPos = invClipPos.xyz / invClipPos.w;

    vec3 normal = normalize(texture(normTex, texCoord).xyz * 2.0 - 1.0);
    vec3 incident = normalize(lightDir * -1.0f);
    vec3 viewDir = normalize(cameraPos - worldPos);
    vec3 halfDir = normalize(incident + viewDir);

    float lambert = clamp(dot(incident, normal), 0.0, 1.0);
    float specFactor = clamp(dot(halfDir, normal), 0.0, 1.0);

    specFactor = pow(specFactor, 60.0);
    vec3 strengthed = lightColour.xyz * lightStrength;

    vec3 pushVal = normal; //* dot(viewDir, normal);
    vec4 shadowProj = shadowMatrix * vec4((worldPos + pushVal), 1.0f);

    float shadow = 1.0;
    vec3 shadowNDC = shadowProj.xyz / shadowProj.w;
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

    diffuseOutput = vec4(strengthed * lambert, 1.0) * shadow;
    specularOutput = vec4(strengthed * specFactor * 0.33, 1.0) * shadow;
    
    //vec3 biasCoord = shadowNDC * 0.5f + 0.5f;
    //specularOutput.rgb = vec3(biasCoord.z);
} 