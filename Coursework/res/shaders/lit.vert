#version 330

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Inputs
in vec3 v_Position;
in vec3 v_Normal;

// Outputs
out vec3 f_Position;
out vec3 f_Normal;
out PointLight f_PointLight0;

// Uniforms
uniform mat4 modelViewProjection;
uniform mat4 modelView;
uniform mat4 normal;
uniform mat4 view;
uniform PointLight pointLight0;

void main()
{
	// Apply model-view-projection matrix to the vertex position
	gl_Position = modelViewProjection * vec4(v_Position, 1);

	// Convert attributes to world space and pass them to the fragment shader
	f_Position = vec3(modelView * vec4(v_Position, 1));
	f_Normal = vec3(normal * vec4(v_Normal, 1));
	f_PointLight0.position = vec3(view * vec4(pointLight0.position, 1));
	f_PointLight0.ambient = pointLight0.ambient;
	f_PointLight0.diffuse = pointLight0.diffuse;
	f_PointLight0.specular = pointLight0.specular;
}
