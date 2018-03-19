#version 120

// Fragment attributes
varying vec4 f_Color;
varying vec2 f_TexCoord;

// Uniforms
uniform sampler2D texture0;

void main()
{
	// Set the fragment colour
	gl_FragColor = texture2D(texture0, f_TexCoord) * f_Color;
}
