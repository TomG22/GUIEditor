#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

uniform mat4 u_CamMatrix;

uniform mat4 u_Model;
uniform mat4 u_Translation;
uniform mat4 u_Rotation;
uniform mat4 u_Scale;

void main()	
{
	crntPos = vec3(u_Model * u_Translation * -u_Rotation * u_Scale * vec4(aPos, 1.0f));
	Normal = aNormal;
	color = aColor;
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
	gl_Position = u_CamMatrix * vec4(crntPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D u_Diffuse0;
uniform sampler2D u_Specular0;

uniform vec4 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_CamPos;

vec4 pointLight() {
	vec3 lightVec = u_LightPos - crntPos;
	float dist = length(lightVec);
	float a = .05;
	float b = .01;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(u_CamPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(u_Diffuse0, texCoord) * (diffuse * inten + ambient) + texture(u_Specular0, texCoord).r * specular * inten) * u_LightColor;
}

vec4 direcLight() {
	float ambient = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(u_CamPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(u_Diffuse0, texCoord) * (diffuse + ambient) + texture(u_Specular0, texCoord).r * specular) * u_LightColor;
}

vec4 spotLight() {

	float outerCone = 0.9f;
	float innerCone = 1.0f;

	
	float ambient = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(u_LightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(u_CamPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(u_Diffuse0, texCoord) * (diffuse * inten + ambient) + texture(u_Specular0, texCoord).r * specular * inten) * u_LightColor;
}

void main()
{
	FragColor = direcLight();
};