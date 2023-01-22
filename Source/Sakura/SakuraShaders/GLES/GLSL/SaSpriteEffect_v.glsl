uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

attribute vec2 aPosition;
attribute vec2 aTexCoord;

varying vec2 vTexCoord;

void main()
{
    vTexCoord = aTexCoord;
    
    mat4 modelProjMatrix = projectionMatrix * modelMatrix;
    gl_Position = modelProjMatrix * vec4(aPosition, 0.0, 1.0);
}
