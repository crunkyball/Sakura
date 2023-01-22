uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec3 aPosition;
attribute vec3 aColour;

varying vec4 vColour;

void main()
{
    vColour = vec4(aColour, 1.0);
    mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
    gl_Position = viewProjectionMatrix * vec4(aPosition, 1.0);
}
