uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec4 aPosition;
attribute vec4 aColour;
attribute vec2 aTexCoord;

varying vec4 vColour;
varying vec2 vTexCoord;

void main()
{
    vColour = aColour;
    vTexCoord = aTexCoord;

    mat4 modelViewMatrix = viewMatrix * modelMatrix;
    mat4 modelViewProjMatrix = projectionMatrix * modelViewMatrix;
    gl_Position = modelViewProjMatrix * aPosition;
}
