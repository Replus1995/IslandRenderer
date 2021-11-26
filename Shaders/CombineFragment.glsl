#version 330 core

uniform sampler2D colourTex;
uniform sampler2D diffuseLight;
uniform sampler2D specularLight;
uniform sampler2D emissiveTex;

in Vertex
{
    vec2 texCoord;
} IN;

out vec4 fragColour;

void main(void)
{
    //vec3 colour = texture(colourTex, IN.texCoord).xyz;
    vec3 colour = pow(texture(colourTex, IN.texCoord).rgb, vec3(2.2));
    vec4 diffuse = texture(diffuseLight, IN.texCoord);
    vec3 specular = texture(specularLight, IN.texCoord).xyz;
    //vec3 emissive = texture(emissiveTex, IN.texCoord).xyz;
    vec3 emissive = pow(texture(emissiveTex, IN.texCoord).rgb, vec3(2.2));

    fragColour.xyz = vec3(0.1) * colour * diffuse.a; // Ambient
    fragColour.xyz += colour * diffuse.rgb; //Diffuse
    fragColour.xyz += specular; // Specular
    fragColour.xyz += emissive; // Emissive
    fragColour.xyz = pow(fragColour.xyz,vec3(1.0/2.2));

    fragColour.a = 1.0;
}