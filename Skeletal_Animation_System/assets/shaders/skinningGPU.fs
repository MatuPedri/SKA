#version 450 core
out vec4 FragColor;

in vec3 norm;

void main()
{
    FragColor = vec4(normalize(norm) * 0.5 + 0.5, 1.0);
} 