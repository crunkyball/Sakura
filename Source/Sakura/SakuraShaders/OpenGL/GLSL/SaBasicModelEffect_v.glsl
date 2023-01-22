uniform mat4 modelViewProj;

attribute vec4 aPosition;
attribute vec3 aNormal;

varying vec3 objectPos;
varying vec3 normal;

void main()
{
    gl_Position = modelViewProj * aPosition;
    objectPos = aPosition.xyz;
    normal = aNormal;
}
