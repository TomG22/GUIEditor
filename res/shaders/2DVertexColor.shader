#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

out vec4 vertexColor;
uniform mat4 u_Proj;

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
    vertexColor = color;
}

#shader fragment
#version 330 core

in vec4 vertexColor;

out vec4 FragColor;

uniform float u_Time;

void main() {
    vec3 color = vertexColor.rgb;

    FragColor = vec4(color, vertexColor.a * sin(u_Time));
}

