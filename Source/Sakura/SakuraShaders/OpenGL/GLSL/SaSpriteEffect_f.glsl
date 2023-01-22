uniform sampler2D texture;
uniform vec4 colour;

varying vec2 vTexCoord;

void main()
{
    gl_FragColor = texture2D(texture, vTexCoord) * colour;
}
