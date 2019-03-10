#version 400 core

in vec3 fragmentColor;

out vec4 fragment;

void main()
{
    fragment = vec4(fragmentColor, 1.0f);
}