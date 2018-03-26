#version 330

// Inputs
in vec3 v_Position;
in vec4 v_Color;

// Outputs
out vec4 f_Color;

// Uniforms
uniform mat4 modelViewProjection;

void main()
{
	// Apply model-view-projection matrix to the vertex position
	gl_Position = modelViewProjection * vec4(v_Position, 1);

	// Pass the vertex colour to the fragment shader
	f_Color = v_Color;
}
