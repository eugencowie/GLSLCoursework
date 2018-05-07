#version 330

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

// Inputs
in vec4 f_Color;
in vec2 f_TexCoord;

// Outputs
out vec4 p_Color;

// Uniforms
uniform Material material;

void main()
{
	// Set the fragment colour
	p_Color = texture(material.diffuse, f_TexCoord) * f_Color;
}
