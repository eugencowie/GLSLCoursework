#version 120

// Vertex attributes
attribute vec3 v_Position;
attribute vec4 v_Color;
attribute vec2 v_TexCoord;

// Fragment attributes
varying vec4 f_Color;
varying vec2 f_TexCoord;

// Uniforms
uniform mat4 modelViewProjection;

void main()
{
	// Apply model-view-projection matrix to the vertex position
	gl_Position = modelViewProjection * vec4(v_Position, 1);

	// Pass the vertex attributes to the fragment shader
	f_Color = v_Color;
	f_TexCoord = v_TexCoord;
}
