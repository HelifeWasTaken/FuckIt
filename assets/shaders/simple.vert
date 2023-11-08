#version 410

layout(location=0) in vec4 vertexPosition;
layout(location=1) in vec4 vertexColor;
out vec4 fcolor;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{
    fcolor = vertexColor;
    gl_Position = vertexPosition * viewMatrix * projectionMatrix * modelMatrix;
}