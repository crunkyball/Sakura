struct Material
{
    vec4 emissive;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec4 colour;
};

static const int MAX_LIGHTS = 2;

uniform vec3 eyePosition;
uniform vec4 globalAmbient;
uniform const int numLights;
uniform Light lights[MAX_LIGHTS];
uniform Material material;

varying vec3 objectPos;
varying vec3 normal;

void ComputeLighting(Light light, 
                     vec3 P, 
                     vec3 N, 
                     vec3 eyePosition, 
                     float shininess,
                     out vec3 lightDiffuse,
                     out vec3 lightSpecular)
{
    vec3 L = normalize(light.position - P);
    float diffuse = max(dot(L, N), 0);
    lightDiffuse = light.colour * diffuse;
    
    vec3 V = normalize(eyePosition - P);
    vec3 H = normalize(L + V);
    float specular = pow(max(dot(H, N), 0), shininess);
    if (diffuse <= 0)
        specular = 0;
    lightSpecular = light.colour * specular;
}

void main()
{
    vec3 emissive = material.emissive;
    vec3 ambient = material.ambient * globalAmbient;
    
    vec3 diffuseSum = 0;
    vec3 specularSum = 0;
    
    for (int i = 0; i < min(numLights, MAX_LIGHTS); i++)
    {
        vec3 lightDiffuse;
        vec3 lightSpecular;
        ComputeLighting(lights[i], objectPos.xyz, normal, eyePosition, material.shininess, lightDiffuse, lightSpecular);
        diffuseSum += lightDiffuse;
        specularSum += lightSpecular;
    }
    
    float3 diffuse = material.diffuse * diffuseSum;
    float3 specular = material.specular * specularSum;
    
    gl_FragColor.xyz = emissive + ambient + diffuse + specular;
    gl_FragColor.w = 1;
    
    //gl_FragColor = vec4(1, 0, 0, 1);
}
