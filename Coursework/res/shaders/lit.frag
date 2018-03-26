#version 330

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Inputs
in vec3 f_Position;
in vec3 f_Normal;
in PointLight f_PointLight0;

// Outputs
out vec4 p_Color;

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
	vec3 ambient = f_PointLight0.ambient;
	vec3 diffuse = diffuse(f_PointLight0.position, f_PointLight0.diffuse);
	vec3 specular = specular(f_PointLight0.position, f_PointLight0.specular);

	// Set the fragment colour
	p_Color = vec4(ambient + diffuse + specular, 1);
}
