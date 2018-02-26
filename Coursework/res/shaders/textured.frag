#version 120

// Fragment attributes
varying vec4 fragmentColor;
varying vec2 fragmentTexCoord;

// Uniforms
uniform sampler2D texture0;

void main()
{
	// Set the fragment colour
	gl_FragColor = texture2D(texture0, fragmentTexCoord) * fragmentColor;
}
