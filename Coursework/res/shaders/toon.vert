#version 330

// Inputs
layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec3 v_Normal;

// Outputs
out vec3 f_Position;
out vec3 f_Normal;

// Uniforms
uniform mat4 modelViewProjection;
uniform mat4 modelView;
uniform mat4 normal;

void main()
{
	// Apply model-view-projection matrix to the vertex position
	gl_Position = modelViewProjection * vec4(v_Position, 1);

	// Convert attributes to world space and pass them to the fragment shader
	f_Position = vec3(modelView * vec4(v_Position, 1));
	f_Normal = vec3(normal * vec4(v_Normal, 1));
}
