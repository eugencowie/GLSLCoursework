#version 330

// Inputs
in vec4 f_Color;

// Outputs
out vec3 p_Color;

void main()
{
	// Set the fragment colour
	p_Color = f_Color;
}
