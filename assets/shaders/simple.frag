#version 410
in vec3 fcolor;
out vec4 fragColor;

void main()
{
    fragColor = vec4(fcolor, 1.0f);
}