uniform vec4 diffuseColour;

varying vec4 vColour;

void main()
{
    gl_FragColor = diffuseColour;
    //gl_FragColor = vColour;
}
