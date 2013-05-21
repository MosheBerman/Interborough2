//
//  RectangularPrism.cpp
//  Interborough2
//
//  Created by Moshe Berman on 5/20/13.
//  Copyright (c) 2013 Moshe Berman. All rights reserved.
//

#include "RectangularPrism.h"

const int kNumberOfVertices = 36;

RectangularPrism::RectangularPrism()
{
	//	Create a shader
	shader = new ShaderProgram("prism.vsh", "prism.fsh");

	//	Create the buffers
	glGenBuffers(1, &vertexBuffer);
	
	//	Bind the vbo to the GL_ARRAY_BUFFER target (which is for buffer data)
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
    /* Back Surface */
    PrismVertex v1 = {1, 1, -1, 0};
    PrismVertex v2 = {1, -1, -1, 0};
    PrismVertex v3 = {-1, -1, -1, 0};
    PrismVertex v4 = {-1, 1, -1, 0};
    
    /* Front Surface */
    PrismVertex v5 = {1, 1, 1, 1};
    PrismVertex v6 = {1, -1, 1, 1};
    PrismVertex v7 = {-1, -1, 1, 1};
    PrismVertex v8 = {-1, 1, 1, 1};
    
    /* Top Surface */
    PrismVertex v9 = {1, 1, -1, 2};
    PrismVertex v10 = {-1, 1, -1, 2};
    PrismVertex v11 = {-1, 1, 1, 2};
    PrismVertex v12 = {1, 1, 1, 2};
    
    
    /* Bottom Surface */
    PrismVertex v13 = {1, -1, -1, 3};
    PrismVertex v14 = {-1, -1, -1, 3};
    PrismVertex v15 = {-1, -1, 1, 3};
    PrismVertex v16 = {1, -1, 1, 3};
    
    /* Left Surface */
    PrismVertex v17 = {-1, 1, -1, 4};
    PrismVertex v18 = {-1, -1, -1, 4};
    PrismVertex v19 = {-1, -1, 1, 4};
    PrismVertex v20 = {-1, 1, 1, 4};
    
    /* Right Surface */
    PrismVertex v21 = {1, 1, -1, 5};
    PrismVertex v22 = {1, -1, -1, 5};
    PrismVertex v23 = {1, -1, 1, 5};
    PrismVertex v24 = {1, 1, 1, 5};
	
	// Create a buffer
	PrismVertex vertices[kNumberOfVertices] = {
		v1, v2, v3,
		v2, v3, v4,
		v5, v6, v7,
		v6, v7, v8,
		v9, v10, v11,
		v10, v11, v12,
		v13, v14, v15,
		v14, v15, v16,
		v17, v18, v19,
		v18, v19, v20,
		v21, v22, v23,
		v22, v23, v24,	
	};
	
	//	Bind the buffer to the VBO on the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(PrismVertex)*kNumberOfVertices, vertices, GL_STATIC_DRAW);  // Static, means it's immutable
}

RectangularPrism::~RectangularPrism()
{
	delete shader;
	glDeleteBuffers(1, &vertexBuffer);
}

#pragma mark - Transform

void RectangularPrism::setTransform(glm::mat4 transform)
{
	this->transform = transform;
}

#pragma mark - Color 

void RectangularPrism::setColor(glm::vec4 color, int face)
{
	this->color[face] = color;
}

#pragma mark - Draw

void RectangularPrism::draw(glm::mat4 worldViewProjectionTransform)
{
	// use shader ("activates it")
	shader->useProgram();
	
	// bind uniforms
	glm::mat4 modelViewProjection = worldViewProjectionTransform * objectTransform;

	//	First Uniform: Transform
	//	NOTE: This is where we name variables in the shader (the c string)
	//	NOTE: glm uses matrices like arrays, so we can
	//	use them as such.
	
	shader->setUniform("objectTransform", &modelViewProjection[0][0]);
	
	//	Second Uniform: Colors
	shader->setUniform("color", this->color, 6);
	
	// ------ bind the VBO ------
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	// bind the input layout
	GLint position = shader->getAttributeLocation("position");
	glEnableVertexAttribArray(position);

	//	TODO: Look this up...
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(PrismVertex), NULL);
	
	GLint face = shader->getAttributeLocation("faceIdentifier");
	glEnableVertexAttribArray(face);
	
	//	TODO: Look this up...
	glVertexAttribPointer(face, 1, GL_FLOAT, GL_FALSE, sizeof(PrismVertex), (GLchar*)12);	//	12 is sizeof(GLfloat)*3
	
	
	// draw
	glDrawArrays(GL_TRIANGLES, 0, kNumberOfVertices);
}