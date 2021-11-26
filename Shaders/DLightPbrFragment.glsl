#version 330 core

const float PI = 3.14159265;

uniform sampler2D colourTex;
uniform sampler2D depthTex;
uniform sampler2D normTex;
uniform sampler2D metallicRoughnessTex;
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

vec3 Schlick_F(vec3 R0, float cosTheta)
{
	return R0 + (vec3(1.0) - R0) * pow(1.0 - cosTheta, 5.0);
}

float GGX_D(vec3 n, vec3 h, float a)
{
    float a2 = a * a;
    float nh = max(dot(n, h), 0);
    float nh2 = nh * nh;
    return a2 / (PI * pow((nh2 * (a2 - 1.0) + 1.0), 2.0));
}

float GGX_G(vec3 n, vec3 v, float a)
{
    float k = pow(a + 1.0, 2.0) / 8.0;
    float nv = max(dot(n, v), 0);
    return nv / (nv * (1 - k) + k);
}

void main(void)
{
    vec2 texCoord = vec2(gl_FragCoord.xy * pixelSize);
    float depth = texture(depthTex, texCoord).r;
    vec3 ndcPos = vec3(texCoord, depth) * 2.0 - 1.0;
    vec4 invClipPos = inverseProjView * vec4(ndcPos, 1.0);
    vec3 worldPos = invClipPos.xyz / invClipPos.w;

    //vec3 colour = texture(colourTex, texCoord).rgb;
    vec3 colour = pow(texture(colourTex, texCoord).rgb, vec3(2.2));
    vec3 normal = normalize(texture(normTex, texCoord).xyz * 2.0 - 1.0);
    vec3 incident = normalize(lightDir * -1.0f);
    vec3 viewDir = normalize(cameraPos - worldPos);
    vec3 halfDir = normalize(incident + viewDir);

    vec3 mroColour = texture(metallicRoughnessTex, texCoord).rgb;
    float metallic = mroColour.r;
    float roughness = mroColour.g;
    float occlution = mroColour.b;

    vec3 reflective = vec3(0.04); 
    reflective = mix(reflective, colour, metallic);
    vec3 F = Schlick_F(reflective, max(dot(halfDir, viewDir), 0));
    float D = GGX_D(normal, halfDir, roughness);
    float G = GGX_G(normal, viewDir, roughness) * GGX_G(normal, incident, roughness);

    vec3 diffuse = (vec3(1.0) - F) * (1.0 - metallic) / PI;
    float nl = dot(normal, incident);
    float nv = dot(normal, viewDir);
    vec3 specular = (F * D * G) / (4 * nl * nv);
    
    vec3 pushVal = normal;
    vec4 shadowProj = shadowMatrix * vec4((worldPos + pushVal), 1.0f);

    float shadow = 1.0;
    vec3 shadowNDC = shadowProj.xyz / shadowProj.w;
    if( abs(shadowNDC.x) < 1.0f &&
        abs(shadowNDC.y) < 1.0f &&
        abs(shadowNDC.z) < 1.0f)
    {
        vec3 biasCoord = shadowNDC * 0.5f + 0.5f;
        float shadowZ = texture(shadowTex, biasCoord.xy).x;
        if(shadowZ < biasCoord.z)
        {
            shadow = 0.0f;
        }
    }

    vec3 radiance = lightColour.xyz * lightStrength * 2;

    diffuseOutput.rgb = diffuse * radiance * nl * shadow;
    diffuseOutput.a = occlution;

    specularOutput.rgb = specular * radiance * nl * shadow;
    specularOutput.a = 1.0;

} 