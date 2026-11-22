#version 450 core
out vec4 FragColor;

in float debugWeight;
in vec3 norm;

void main()
{
    FragColor = vec4(debugWeight, 0.0, 1.0 - debugWeight, 1.0);
} 