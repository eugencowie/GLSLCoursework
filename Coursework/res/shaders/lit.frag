#version 330

struct Material {
	float shininess;
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

// Inputs
in vec3 f_Position;
in vec3 f_Normal;

// Outputs
out vec4 p_Color;

// Uniform
uniform mat4 view;
uniform Material material0;
uniform PointLight pointLight0;

vec3 diffuse(vec3 pos, vec3 color)
{
	vec3 normal = normalize(f_Normal);
	vec3 lightDir = normalize(pos - f_Position);
	float strength = max(dot(normal, lightDir), 0);
	return strength * color;
}

vec3 specular(vec3 pos, vec3 color)
{
	vec3 normal = normalize(f_Normal);
	vec3 lightDir = normalize(pos - f_Position);
	vec3 viewDir = normalize(-f_Position);
	vec3 reflectDir = reflect(-lightDir, normal);
	float strength = 0.5 * pow(max(dot(viewDir, reflectDir), 0), 128);
	return strength * color;
}

void main()
{
	vec3 lightPos = vec3(view * vec4(pointLight0.position, 1));

	vec3 ambient = pointLight0.ambient;
	vec3 diffuse = diffuse(lightPos, pointLight0.diffuse);
	vec3 specular = specular(lightPos, pointLight0.specular);

	// Set the fragment colour
	p_Color = vec4(ambient + diffuse + specular, 1);
}
