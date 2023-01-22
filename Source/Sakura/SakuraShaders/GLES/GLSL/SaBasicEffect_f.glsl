uniform sampler2D texture;

varying lowp vec4 vColour;
varying lowp vec2 vTexCoord;

void main()
{
    gl_FragColor = texture2D(texture, vTexCoord) * vColour;
}
