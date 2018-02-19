#version 120

// Vertex attributes
attribute vec3 vertexPosition;
attribute vec4 vertexColor;

// Fragment attributes
varying vec4 fragmentColor;

// Uniforms
uniform mat4 modelViewProjection;

void main()
{
	// Apply model-view-projection matrix to the vertex position
	gl_Position = modelViewProjection * vec4(vertexPosition, 1);

	// Pass the vertex colour to the fragment shader
	fragmentColor = vertexColor;
}
