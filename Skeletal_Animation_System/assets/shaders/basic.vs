#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 norm;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    norm = mat3(transpose(inverse(view * model))) * normalize(aNorm);
}