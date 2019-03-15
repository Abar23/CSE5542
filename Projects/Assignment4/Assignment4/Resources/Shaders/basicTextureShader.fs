#version 400 core

in vec2 fragmentTexCoords;

uniform sampler2D cubeTexture;

out vec4 fragment;

void main()
{
    fragment = texture(cubeTexture, fragmentTexCoords);
}