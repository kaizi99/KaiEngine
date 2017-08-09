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

#pragma once

#include <stack>
#include <vector>
#include <memory>

#include "../../rendering/resources/texturemanager.h"
#include "../../rendering/resources/MeshManager.h"
#include "../../rendering/resources/shadermanager.h"
#include "../input.h"

class Gamestate;
class Window;

struct GLFWwindow;

class GamestateManager
{
public:
	GamestateManager();
	~GamestateManager();
	static GamestateManager* instance;

	void run(std::unique_ptr<Gamestate> gamestate);

	void PopGamestate();
	void PushGamestate(std::unique_ptr<Gamestate> gamestate);

	float getAspectRatio();

    void closeWindow();

	ShaderManager& getShaderManager();
	TextureManager& getTextureManager();
	MeshManager& getMeshManager();
    Input& getInput();
private:
	GLFWwindow* m_window;

	ShaderManager m_shaderManager;
	TextureManager m_textureManager;
	MeshManager m_meshManager;

    Input m_input;

	std::stack<std::unique_ptr<Gamestate>> m_gamestates;
	std::unique_ptr<Gamestate> m_currentGamestate;
	std::unique_ptr<Gamestate> m_toPush;
	bool m_popGamestate;
};
