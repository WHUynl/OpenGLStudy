#version 330 core 

in vec2 TexCoords;
out vec4 Fragcolor;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    Fragcolor = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}