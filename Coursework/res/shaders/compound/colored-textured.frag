#version 330

// Inputs
in vec4 f_Color;
in vec2 f_TexCoord;

// Outputs
out vec4 p_Color;

// Uniforms
uniform sampler2D texture0;

void main()
{
	// Set the fragment colour
	p_Color = texture(texture0, f_TexCoord) * f_Color;
}
