#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 vertexColor;
out vec2 fragTexCoord;

uniform mat4 u_Proj;

void main() {
    gl_Position = u_Proj * vec4(position, 0.0, 1.0);
    vertexColor = color;
    fragTexCoord = texCoord;
}

#shader fragment
#version 330 core

in vec4 vertexColor;
in vec2 fragTexCoord;

out vec4 FragColor;

uniform vec2 u_Size;
uniform vec2 u_TopLeftPos;
uniform float u_Radius;

float roundedBoxSDF(vec2 centerPos, vec2 halfSize, float radius) {
    return length(max(abs(centerPos) - halfSize + radius, 0.0)) - radius;
}

void main() {
    vec2 fragPos = fragTexCoord * u_Size + u_TopLeftPos;

    vec2 rectCenter = u_TopLeftPos + u_Size * 0.5;
    vec2 halfSize = u_Size * 0.5;

    float distance = roundedBoxSDF(fragPos - rectCenter, halfSize, u_Radius);

    if (distance > 0.0) {
        discard;
    }

    FragColor = vertexColor;
}
