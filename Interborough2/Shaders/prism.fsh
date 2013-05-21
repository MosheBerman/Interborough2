/* Input */

varying float faceIdentifierAsOutput;

uniform vec4 color[6];

/* Output a color */

void main()
{
	int id = int(faceIdentifierAsOutput);
	gl_FragColor = color[id];
}