#version 330

struct Material {
	float shininess;
};

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	float linear;
	float quadratic;
	float constant;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Inputs
in vec3 f_Position;
in vec3 f_Normal;

// Outputs
out vec4 p_Color;

// Uniform
uniform mat4 view;
uniform Material material;
uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-vec3(view * vec4(light.direction, 1)));
	vec3 reflectDir = reflect(-lightDir, normal);

	vec3 ambient = light.ambient;
	vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0);
	vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0), material.shininess);

	return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightPos = vec3(view * vec4(light.position, 1));
	vec3 lightDir = normalize(lightPos - f_Position);
	vec3 reflectDir = reflect(-lightDir, normal);

	float dist = length(lightPos - f_Position);
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	vec3 ambient = light.ambient * attenuation;
	vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0) * attenuation;
	vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0), material.shininess) * attenuation;

	return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightPos = vec3(view * vec4(light.position, 1));
	vec3 lightDir = normalize(lightPos - f_Position);
	vec3 reflectDir = reflect(-lightDir, normal);

	float dist = length(lightPos - f_Position);
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));  

	float theta = dot(lightDir, normalize(-vec3(view * vec4(light.direction, 1)))); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0, 1);

	vec3 ambient = light.ambient * attenuation * intensity;
	vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0) * attenuation * intensity;
	vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0), material.shininess) * attenuation * intensity;

	return (ambient + diffuse + specular);
}

void main()
{
	vec3 normal = normalize(f_Normal);
	vec3 viewDir = normalize(-f_Position);

	vec3 result = ambientLight;
	
	result += calculatePointLight(pointLight, normal, viewDir);

	// Set the fragment colour
	p_Color = vec4(result, 1);
}
