#version 330 core

const float PI = 3.14159265;

uniform sampler2D diffuseTex;
uniform sampler2D normTex;
uniform samplerCube cubeTex;

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
    mat3 TBN =  mat3(normalize(IN.tangent), normalize(IN.binormal), normalize(IN.normal));

    vec3 colour = texture(diffuseTex, IN.texCoord).rgb;
    vec3 normal = texture(normTex, IN.texCoord).rgb;
    normal = normalize(TBN * normalize(normal * 2.0 - 1.0));
    vec3 incident = normalize(lightDir * -1.0);
    vec3 viewDir = normalize(cameraPos - IN.worldPos);
    vec3 halfDir = normalize(incident + viewDir);

    float metallic = 1;
    float roughness = 0.5;

    vec3 reflective = vec3(0.04); 
    reflective = mix(reflective, colour, metallic);
    vec3 F = Schlick_F(reflective, max(dot(halfDir, viewDir), 0));
    float D = GGX_D(normal, halfDir, roughness);
    float G = GGX_G(normal, viewDir, roughness) * GGX_G(normal, incident, roughness);

    vec3 diffuse = (vec3(1.0) - F) * (1.0 - metallic) / PI;
    float nl = dot(normal, incident);
    float nv = dot(normal, viewDir);
    vec3 specular = (F * D * G) / (4 * nl * nv);
    //specular = max(specular, vec3(0,0,0));
    //specular *= -1;

    vec3 radiance = lightColour.xyz * lightStrength * 2;

    fragColour.xyz = vec3(0.1) * colour; // Ambient
    fragColour.xyz += colour * diffuse * radiance * nl; //Diffuse
    fragColour.xyz += specular * radiance * nl; // Specular

    vec3 reflectDir = reflect(-viewDir,normalize(IN.normal));
    vec4 reflectTex = texture(cubeTex,reflectDir);
    fragColour.xyz = fragColour.xyz + reflectTex.xyz * 0.3;

    //fragColour.xyz = colour;
    fragColour.a = 0.5;

    //fragColour = vec4(diffuse.rgb, 0.7f);
}