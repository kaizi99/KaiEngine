/*
    KaiEngine - Deferred PBR Engine
    Copyright (C) 2017 Kai-Uwe Zimdars

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "shader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string type)
	: m_locations()
{
	std::string path = "./res/shader/" + type;
	std::ifstream vShaderIFStream, fShaderIFStream;
	std::stringstream vShaderStringStream, fShaderStringStream;
	std::string vShaderString, fShaderString;

	vShaderIFStream.open(path + ".vshader");
	vShaderStringStream << vShaderIFStream.rdbuf();
	vShaderString = vShaderStringStream.str();
	const char* vShaderCode = vShaderString.c_str();

	fShaderIFStream.open(path + ".fshader");
	fShaderStringStream << fShaderIFStream.rdbuf();
	fShaderString = fShaderStringStream.str();
	const char* fShaderCode = fShaderString.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex Shader compilation error:" << std::endl << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment Shader compilation error:" << std::endl << infoLog << std::endl;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::enable()
{
	glUseProgram(m_ID);
}

void Shader::set(std::string name, int value)
{
	enable();
	glUniform1i(getLocation(name), value);
}

void Shader::set(std::string name, float value)
{
	enable();
	glUniform1f(getLocation(name), value);
}

void Shader::set(std::string name, bool value)
{
	enable();
	glUniform1i(getLocation(name), (int)value);
}

void Shader::set(std::string name, glm::vec3 value)
{
	enable();
	glUniform3f(getLocation(name), value.x, value.y, value.z);
}

void Shader::set(std::string name, glm::mat4 value)
{
	enable();
	glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

int Shader::getLocation(std::string name)
{
	auto pair = m_locations.find(name);
	if (pair == m_locations.end())
	{
		int location = glGetUniformLocation(m_ID, name.c_str());
		m_locations.insert(std::make_pair(name, location));
		return location;
	}

	return pair->second;
}
