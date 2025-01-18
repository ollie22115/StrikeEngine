#include "Program.h"
#include <fstream>
#include <string>
#include <iostream>

GLP::Shader::Shader(const GLenum type) : type(type){
	id = glCreateShader(type);
}

int GLP::Shader::compileShader(const char* src){
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	GLint compilationResult = GL_TRUE;

#ifdef GLP_DEBUG
	glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);

	char infoLog[512];
	if (!compilationResult) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "Shader Failed to Load!\n";
		std::cout << infoLog << "\n";
	}
#endif

	return compilationResult;
}

GLP::Shader::~Shader(){
	glDeleteShader(id);
}


void GLP::Program::init(){
	id = glCreateProgram();
}

void GLP::Program::compileShaderFile(GLenum type, const char* path){
	//TODO!!! Test
	std::ifstream file(path);

	std::string line;
	std::string src;
	while (getline(file, line))
		src += line + "\n";
	
	compileShader(type, src.c_str());
}

void GLP::Program::compileShader(GLenum type, const char* src){
	shaders.emplace_back(type);
	shaders[shaders.size() - 1].compileShader(src);
	glAttachShader(id, shaders[shaders.size() - 1].getID());
}

GLint GLP::Program::linkProgram() {
	glLinkProgram(id);
	shaders.clear();

	GLint linkResult;
	glGetProgramiv(id, GL_LINK_STATUS, &linkResult);

#ifdef GLP_DEBUG
	char infoLog3[512];
	if (!linkResult) {
		glGetProgramInfoLog(id, 512, NULL, infoLog3);
		std::cout << infoLog3 << std::endl;
	}
#endif

	return linkResult;
}

void GLP::Program::useProgram(){
	glUseProgram(id);
}

bool GLP::Program::setUniform4f(const char* uniformName, float f1, float f2, float f3, float f4){
	
	if (uniforms.find(uniformName) == uniforms.end()) {
		int uniformLocation = glGetUniformLocation(id, uniformName);
		if (uniformLocation < 0) return false;
		
		uniforms[uniformName] = uniformLocation;
	}

	glUniform4f(uniforms[uniformName], f1, f2, f3, f4);

	return true;
}

GLP::Program::~Program() {
	glDeleteProgram(id);
}
