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

#include "ingame.h"

#include <vector>
#include "../../rendering/vertex.h"
#include "gamestatemanager.h"

std::vector<Vertex> vertices = {
	{ glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(), glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(), glm::vec2(0.0f, 1.0f) },
};

std::vector<int> indices = {
	0, 1, 3,
	1, 2, 3
};

IngameState::IngameState()
    : m_camera(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0))
	, m_test(TexturedModel(GamestateManager::instance->getMeshManager().createMesh(vertices, indices), Material("container2")), &m_camera, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1))
{
    GamestateManager::instance->getInput().setCamera(&m_camera);
}

IngameState::~IngameState()
{
    GamestateManager::instance->getInput().setCamera(nullptr);
}

void IngameState::update(double deltaTime)
{
    m_camera.update(deltaTime);
}

void IngameState::render()
{
	m_test.render();
}

void IngameState::clean()
{

}
