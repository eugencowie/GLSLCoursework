#version 120

// Fragment attributes
varying vec4 f_Color;

void main()
{
	// Set the fragment colour
	gl_FragColor = f_Color;
}
