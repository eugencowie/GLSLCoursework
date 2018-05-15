#version 330

// Inputs
layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec4 v_Normal;

// Outputs
out vec4 f_Color;

// Uniforms
uniform mat4 modelViewProjection;

void main()
{
	// Apply model-view-projection matrix to the vertex position
	gl_Position = modelViewProjection * vec4(v_Position, 1);

	// Pass the vertex normal to the fragment shader
	f_Color = abs(v_Normal);
}
