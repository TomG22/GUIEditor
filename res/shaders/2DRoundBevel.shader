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

uniform vec2 u_LightDir = normalize(vec2(-1.0, -1.0));
uniform float u_LightStrength = 0.3;

uniform vec2 u_ShadowDir = normalize(vec2(1.0, 1.0));
uniform float u_ShadowStrength = 0.3;

float sdRoundBox(vec2 p, vec2 b, float r) {
    vec2 q = abs(p) - b;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}

void main() {
    vec2 fragPos = fragTexCoord * u_Size + u_TopLeftPos;

    vec2 rectCenter = u_TopLeftPos + u_Size * 0.5;
    vec2 halfSize = u_Size * 0.5;

    float distance = sdRoundBox(fragPos - rectCenter, halfSize - u_Radius, u_Radius);

    if (distance > 0.0) {
        discard;
    }

    float bevelAlpha = smoothstep(0.0, -u_Radius, distance);

    float delta = 0.5;
    vec2 offsetX = vec2(delta, 0.0);
    vec2 offsetY = vec2(0.0, delta);

    float dX = sdRoundBox(fragPos - rectCenter + offsetX, halfSize - u_Radius, u_Radius) -
        sdRoundBox(fragPos - rectCenter - offsetX, halfSize - u_Radius, u_Radius);
    float dY = sdRoundBox(fragPos - rectCenter + offsetY, halfSize - u_Radius, u_Radius) -
        sdRoundBox(fragPos - rectCenter - offsetY, halfSize - u_Radius, u_Radius);

    vec2 normal = normalize(vec2(dX, dY));

    float lightFactor = clamp(dot(normal, -u_LightDir), 0.0, 1.0) * u_LightStrength;

    float shadowFactor = clamp(dot(normal, -u_ShadowDir), 0.0, 1.0) * u_ShadowStrength;

    vec3 baseColor = vertexColor.rgb;
    vec3 bevelColor = baseColor + lightFactor - shadowFactor;

    FragColor = vec4(mix(bevelColor, baseColor, bevelAlpha), vertexColor.a);
}

