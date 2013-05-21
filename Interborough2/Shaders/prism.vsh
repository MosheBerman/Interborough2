/* Input */
attribute vec3 position;
attribute float faceIdentifier;

uniform mat4 objectTransform;

/* Output */
varying float faceIdentifierAsOutput;

void main()
{
	faceIdentifierAsOutput = faceIdentifier;
	//	Convert position into a vec4
	gl_Position = vec4(position, 1.0);
}

