//
//  ShaderProgram.h
//  Interborough2
//
//  Created by Moshe Berman on 5/20/13.
//  Copyright (c) 2013 Moshe Berman. All rights reserved.
//

#ifndef __Interborough2__ShaderProgram__
#define __Interborough2__ShaderProgram__

#include "../Interoborough.h"

class ShaderProgram {
	
	/* Shader Compiler Methods */
	
	//	Takes path to a file and a shaderType
	bool addShader(GLchar* file, GLenum shaderType);
	
	//	Takes a shader type, input source, and a pointer to our final shader
	bool compile(GLuint shaderType, const GLchar *sourceCode, GLint *shader);
	
	/* Shader Compiler Member Variables */
	
	//	The compiled shader program
	GLuint shaderProgram;
	
	//	Shader references for memory management
	GLuint vertexShaderIdentifier;
	GLuint fragmentShaderIdentifier;
	
	/* Shader Linker */
	
	bool link();
	
public:
	ShaderProgram(std::string vertexShader, std::string fragmentShader);
	~ShaderProgram();
	
	/* Use Program - "activate" the shader */
	void useProgram();

	/* Ask the shader where the attributes are */
	GLint getAttributeLocation(const char* attributeName);
	
	/* Uniform by name methods */
	
	void setUniform(const char *name, const glm::vec3 &v);
	void setUniform(const char *name, const glm::vec4 &v);
	void setUniform(const char *name, const glm::mat4 &m);
	void setUniform(const char *name, const glm::mat3 &m);
	void setUniform(const char *name, float val);
	void setUniform(const char *name, int val);
	void setUniform(const char *name, bool val);
	void setUniform(const char *name, const glm::vec4 *v, int count);
	
	/* Uniform by index methods */
	
	void setUniform(int index, const glm::vec2 &v);
	void setUniform(int index, const glm::vec3 &v);
	void setUniform(int index, const glm::vec4 &v);
	void setUniform(int index, const glm::mat3 &m);
	void setUniform(int index, const glm::mat4 &m);
	void setUniform(int index, float val);
	void setUniform(int index, int val);
	void setUniform(int index, bool val);
};

#endif /* defined(__Interborough2__ShaderProgram__) */

