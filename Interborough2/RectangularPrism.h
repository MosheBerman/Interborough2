//
//  RectangularPrism.h
//  Interborough2
//
//  Created by Moshe Berman on 5/20/13.
//  Copyright (c) 2013 Moshe Berman. All rights reserved.
//

#ifndef __Interborough2__RectangularPrism__
#define __Interborough2__RectangularPrism__

#include "Interoborough.h"
#include "ShaderProgram.h"

struct PrismVertex
{
	float position[3];
	float faceIdentifer;
};

class RectangularPrism {
	
	//	Use this to set up the object
	glm::mat4 objectTransform;
	
	//	The shader
	ShaderProgram *shader;
	
	//	"vbo"
	GLuint vertexBuffer;
	
	//	Color
	glm::vec4 color[6];
	
	//	Transform
	glm::mat4 transform;
	
public:
	
	RectangularPrism();
	~RectangularPrism();
	
	void setTransform(glm::mat4 transform);
	void setColor(glm::vec4 color, int face);
	//TODO: setTexture
	
	// Takes a worldview from the main
	void draw(glm::mat4 worldViewProjection);
};

typedef enum {
	kPrismFaceBack = 0,
	kPrismFaceFront,
	kPrismFaceTop,
	kPrismFaceBottom,
	kPrismFaceLeft,
	kPrismFaceRight
	
} kPrismFace;

#endif /* defined(__Interborough2__RectangularPrism__) */
