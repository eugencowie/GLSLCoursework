#version 330

// Inputs
layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec3 v_Normal;
layout (location = 3) in vec2 v_TexCoord;

// Outputs
out vec3 f_Position;
out vec3 f_Normal;
out vec2 f_TexCoord;

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
	f_TexCoord = v_TexCoord;
}
