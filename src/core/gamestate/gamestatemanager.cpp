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

#include "gamestatemanager.h"
#include "gamestate.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

GamestateManager* GamestateManager::instance;

GamestateManager::GamestateManager()
	: m_popGamestate(false)
{
	instance = this;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create the window!" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

GamestateManager::~GamestateManager()
{
	glfwTerminate();
}

void GamestateManager::run(std::unique_ptr<Gamestate> gamestate)
{
	gamestate->setGamestateManager(this);
	m_gamestates.push(std::move(gamestate));

	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		double currentFrame = glfwGetTime();
		double deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_currentGamestate = std::move(m_gamestates.top());
		m_gamestates.pop();

		m_currentGamestate->update(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT);

		m_currentGamestate->render();

		glfwSwapBuffers(m_window);

		if (m_popGamestate)
		{
			m_popGamestate = false;
			m_currentGamestate->clean();
		}
		else
			m_gamestates.push(std::move(m_currentGamestate));

		if (m_toPush != nullptr)
		{
			m_gamestates.push(std::move(m_toPush));
		}
	}
}

void GamestateManager::PopGamestate()
{
	m_popGamestate = true;
}

void GamestateManager::PushGamestate(std::unique_ptr<Gamestate> gamestate)
{
	gamestate->setGamestateManager(this);
	m_toPush = std::move(gamestate);
}

float GamestateManager::getAspectRatio()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	return (float)width / (float)height;
}

ShaderManager& GamestateManager::getShaderManager()
{
	return m_shaderManager;
}

TextureManager& GamestateManager::getTextureManager()
{
	return m_textureManager;
}

MeshManager& GamestateManager::getMeshManager()
{
	return m_meshManager;
}
