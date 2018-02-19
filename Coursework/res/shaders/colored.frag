#version 120

// Fragment attributes
varying vec4 fragmentColor;

void main()
{
	// Set the fragment colour
	gl_FragColor = fragmentColor;
}
