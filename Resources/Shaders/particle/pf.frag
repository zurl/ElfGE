#version 330 core
in vec2 TexCoord;
in vec4 tone;
out vec4 color;

uniform sampler2D tex;

void main()
{
    //vec4 FragColor = texture(tex, TexCoord);
    //loat brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));

    color = vec4(texture(tex, TexCoord)*tone);
    //color.a *= brightness;
}