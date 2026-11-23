#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in ivec4 aBoneIds;
layout (location = 3) in vec4  aBoneWeights;

const int MAX_BONES = 64;
uniform mat4 bones[MAX_BONES];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 norm;

void main()
{
    mat4 skin = mat4(0.0);
    for(int i = 0; i < 4; ++i){
        if(aBoneWeights[i] > 0.0){
            skin += bones[aBoneIds[i]] * aBoneWeights[i];
        }
    }

    vec4 pos = skin * vec4(aPos, 1.0);
    gl_Position = projection * view * model * pos;
    norm = mat3(transpose(inverse(view * model))) * normalize(mat3(skin) * aNorm);
}