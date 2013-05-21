//
//  ShaderProgram.cpp
//  Interborough2
//
//  Created by Moshe Berman on 5/20/13.
//  Copyright (c) 2013 Moshe Berman. All rights reserved.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexShader, std::string fragmentShader)
{
	/* Create */
	
	this->shaderProgram = glCreateProgram();
	
	/* Compile Shaders */
	
	//	Add our two shaders - OpenGL 4 support more kinds of shaders.
	bool vertexShaderDidSucceed = addShader((GLchar *)vertexShader.c_str(), GL_VERTEX_SHADER);
	bool fragmentShaderDidSucceed = addShader((GLchar *)fragmentShader.c_str(), GL_FRAGMENT_SHADER);
	
	//	If either failed, throw
	if (!vertexShaderDidSucceed) {
		throw "Vertex shader failed";
	}
	
	if (!fragmentShaderDidSucceed) {
		throw "Fragment shader failed";
	}
	
	/* Link */
	
	if(!link())
	{
		throw "Linker failed";
	}
}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(shaderProgram, vertexShaderIdentifier);
	glDetachShader(shaderProgram, fragmentShaderIdentifier);
	glDeleteShader(vertexShaderIdentifier);
	glDeleteShader(fragmentShaderIdentifier);
	glDeleteProgram(shaderProgram);
}

#pragma mark - Load Source into Compiler

/**
 *	file: a path to the shader file
 *  shaderType: GL_VERTEX_SHADER || GL_FRAGMENT_SHADER
 *
 */

bool ShaderProgram::addShader(GLchar* file, GLenum shaderType)
{
	//	Build out a path to a string
	std::string filename = kShaderPath + std::string(file);
	
	// Read out the input
	//	TODO: Implement static util class for this
	std::ifstream input(filename);
	std::string output = "";
	std::string line;
	while(std::getline(input, line)) {
		output.append(line);
		output.append("\n");
	}
	input.close();
	
	//	Load the shader code
	GLchar* shaderCode = (GLchar*)output.c_str();
	
	//	Create the shader
	GLint shader;
	
	//	Attempt to compile
	if(!compile(shaderType, shaderCode, &shader))
	{
		return false;
	}
	
	//	Wire up the newly compiled shader
	glAttachShader(shaderProgram, shader);
	
	//	Keep a reference to the shader for cleanup
	shaderType == GL_VERTEX_SHADER ? vertexShaderIdentifier = shader : fragmentShaderIdentifier = shader;
    
    return true;
}

#pragma mark - Compile a Shader From Source

/**
 *	type: GL_VERTEX_SHADER || GL_FRAGMENT_SHADER
 *  sourceCode: A charactar array which is our program
 *	shader: an unitialized pointer to a shader - output
 *
 */

bool ShaderProgram::compile(GLuint shaderType, const GLchar *sourceCode, GLint *shader)
{

	//	Tells us if the compilation succeed
	GLint compilationResult;
	
	// Load an uncompiled shader
	*shader = glCreateShader(shaderType);
	
	//	Load the source into a buffer
	glShaderSource(*shader, 1, &sourceCode, NULL);
	
	//	Compile - what does this big red button do?
	glCompileShader(*shader);
	
	//	Get compilation status
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &compilationResult);
	
	//	If the compilation failed...
	if (GL_FALSE == compilationResult)
	{
		
		//	Depending on the shader type, set the diagnostic string
		const char *error = shaderType == GL_VERTEX_SHADER ? "Vertex shader compilation failed.\n" : "Fragment shader compilation failed.\n";
		
		//	Print to stderr
		fprintf(stderr, "%s", error);
		
		//	Get the length of the GL  compilation log
		GLint logLen;
		
		//	Read out the log
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLen);
		
		//	If there's an error...
		if(logLen > 0)
		{
			//	Allocate enough memory for our log
			char* log = (char*)malloc(logLen);
			
			//	Read out the actual log into our buffer
			GLsizei written;
			glGetShaderInfoLog(*shader, logLen, &written, log);
			
			//	Output to stderr
			fprintf(stderr, "Shader log: \n%s", log);
			
			//	Free memory...  Nothing clever here
			free(log);
		}
		
		return false;
	}
	
	return true;
}

#pragma mark - Linker

/**
 *	Links a compiled shader
 */

bool ShaderProgram::link()
{

	//	Link here...
	glLinkProgram(shaderProgram);
	
	//	Grab the result of the linker
	GLint linkerResult;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkerResult );
	
	//	If the linking failed...
	if( GL_FALSE == linkerResult )
	{
		
		//	Output to stderr
		fprintf( stderr, "Failed to link shader program!\n" );

		//	Get the length of the error info
		GLint logLen;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLen);
		
		//	If there's error info...
		if(logLen > 0)
		{	
			//	allocate a buffer, log, and free it
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(shaderProgram, logLen, &written, log);
			fprintf(stderr, "Program log: \n%s", log);
			free(log);
		}
		
		return false;
	}
	
	return true;
}

#pragma mark - Use Program

void ShaderProgram::useProgram()
{
	glUseProgram(shaderProgram);
}

#pragma mark - Attribute Location

/**
 *	Ask the program for the attribute ID
 */

GLint ShaderProgram::getAttributeLocation(const char* attributeName)
{
	return glGetAttribLocation(shaderProgram, attributeName);
}

#pragma mark - Uniform Setters

/* Uniform by name methods */

void ShaderProgram::setUniform(const char *name, const glm::vec3 &v)
{
	int index = glGetUniformLocation(shaderProgram, name);
	GLfloat vect[] = {v.x, v.y, v.z};
	glUniform3fv(index, 1, vect);
}
void ShaderProgram::setUniform(const char *name, const glm::vec4 &v)
{
	int index = glGetUniformLocation(shaderProgram, name);
	GLfloat vect[] = {v.x, v.y, v.z, v.w};
	glUniform4fv(index, 1, vect);
}

void ShaderProgram::setUniform(const char *name, const glm::mat4 &m)
{
	int index = glGetUniformLocation(shaderProgram, name);
	glUniformMatrix4fv(index, 1, GL_FALSE, &m[0][0]);
}
void ShaderProgram::setUniform(const char *name, const glm::mat3 &m)
{
	int index = glGetUniformLocation(shaderProgram, name);
	glUniformMatrix3fv(index, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::setUniform(const char *name, float val)
{
	int index = glGetUniformLocation(shaderProgram, name);
	glUniform1f(index, val);
}

void ShaderProgram::setUniform(const char *name, int val)
{
	int index = glGetUniformLocation(shaderProgram, name);
	glUniform1i(index, val);
}

void ShaderProgram::setUniform(const char *name, bool val)
{
	int index = glGetUniformLocation(shaderProgram, name);
	glUniform1ui(index, val);
}

void ShaderProgram::setUniform(const char *name, const glm::vec4 *v, GLsizei count)
{
	int index = glGetUniformLocation(shaderProgram, name);
	// Sends the uniform to the shader
	glUniform4fv(index, count, &v[0][0]);
}

/* Uniform by index methods */
void ShaderProgram::setUniform(int index, const glm::vec2 &v)
{
	GLfloat vect[] = {v.x, v.y };
	glUniform2fv(index, 1, vect);
}

void ShaderProgram::setUniform(int index, const glm::vec3 &v)
{
	GLfloat vect[] = {v.x, v.y, v.z};
	glUniform3fv(index, 1, vect);
}

void ShaderProgram::setUniform(int index, const glm::vec4 &v)
{
	GLfloat vect[] = {v.x, v.y, v.z, v.w};
	glUniform4fv(index, 1, vect);
}

void ShaderProgram::setUniform(int index, const glm::mat3 &m)
{
	glUniformMatrix3fv(index, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::setUniform(int index, const glm::mat4 &m)
{
	glUniformMatrix4fv(index, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::setUniform(int index, float val)
{
	glUniform1f(index, val);
}

void ShaderProgram::setUniform(int index, int val)
{
	glUniform1i(index, val);
}

void ShaderProgram::setUniform(int index, bool val)
{
	glUniform1ui(index, val);
}


