uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec4 aPosition;
attribute vec3 aNormal;

varying vec4 vColour;

void main()
{
    /*vec4 lightPos = vec4(100.0, 100.0, 100.0, 1.0);
    vec4 lightColour = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 lightAmbient = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 matDiffuse = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 matSpecular = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 matAmbient = vec4(1.0, 0.0, 0.0, 1.0);
    float matShininess = 0.5;

    mat4 modelViewMatrix = viewMatrix * modelMatrix;
    mat4 modelViewProjMatrix = projectionMatrix * modelViewMatrix;
    
    mat3 normalMatrix = mat3(modelViewMatrix);
    vec3 N = normalize(normalMatrix * aNormal);
    
    vec4 pos = modelViewMatrix * aPosition;
    vec3 lightPos = (modelViewMatrix * lightPos).xyz;
    vec3 lightDir = (lightPos - pos.xyz).xyz;
    
    float NdotL = max(dot(N, lightDir.xyz), 0.0);
    
    float dist = length(lightDir);
    
    vec3 E = -pos.xyz;
    
    vec4 finalColour = matAmbient * lightAmbient;
  
    if (NdotL > 0.0)
    {
        vec3 HV = normalize(lightPos + E);
        finalColour += matDiffuse * lightColour * NdotL;
        float NdotHV = max(dot(N, HV), 0.0);
        finalColour += matSpecular * lightColour * pow(NdotHV, matShininess);
    }
    
    vColour = vec4(aNormal, 1.0);//finalColour;
    if (vColour[0] > 0.5)
        vColour[0] = 1.0;
    else if (vColour[0] < -0.5)
        vColour[0] = 0.5;
    else
        vColour[0] = 0.0;
        
    if (vColour[1] > 0.5)
        vColour[1] = 1.0;
    else if (vColour[1] < -0.5)
        vColour[1] = 0.5;
    else
        vColour[1] = 0.0;
        
    if (vColour[2] > 0.5)
        vColour[2] = 1.0;
    else if (vColour[2] < -0.5)
        vColour[2] = 0.5;
    else
        vColour[2] = 0.0;
    
    //vColour = finalColour;//vec4(1.0, 0.0, 0.0, 1.0);
    
    gl_Position = projectionMatrix * pos;*/
    
    mat4 modelViewMatrix = viewMatrix * modelMatrix;
    mat4 modelViewProjMatrix = projectionMatrix * modelViewMatrix;
    
    vColour = vec4(aNormal, 1.0);//finalColour;
    if (vColour[0] > 0.5)
        vColour[0] = 1.0;
    else if (vColour[0] < -0.5)
        vColour[0] = 0.5;
    else
        vColour[0] = 0.0;
        
    if (vColour[1] > 0.5)
        vColour[1] = 1.0;
    else if (vColour[1] < -0.5)
        vColour[1] = 0.5;
    else
        vColour[1] = 0.0;
        
    if (vColour[2] > 0.5)
        vColour[2] = 1.0;
    else if (vColour[2] < -0.5)
        vColour[2] = 0.5;
    else
        vColour[2] = 0.0;
    
    gl_Position = modelViewProjMatrix * aPosition;
}
