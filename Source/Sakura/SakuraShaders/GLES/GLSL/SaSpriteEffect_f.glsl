uniform sampler2D texture;
uniform lowp vec4 colour;

varying lowp vec2 vTexCoord;

void main()
{
    gl_FragColor = texture2D(texture, vTexCoord) * colour;
}
