#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 ModelMatrix;

out vec4 VertexColor; 

void main()
{
    gl_Position = ModelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    VertexColor = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}