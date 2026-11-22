#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in ivec4 aBoneIds;
layout (location = 3) in vec4  aBoneWeights;

out float debugWeight;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 norm;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    norm = mat3(transpose(inverse(view * model))) * normalize(aNorm);

    const int TARGET = 15;          // prueba con otros huesos
    debugWeight = 0.0;
    for (int k = 0; k < 4; ++k)
        if (aBoneIds[k] == TARGET)
            debugWeight += aBoneWeights[k];
}