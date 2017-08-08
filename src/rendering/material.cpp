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

#include "material.h"

#include "shader.h"
#include "texture.h"

#include "../core/gamestate/gamestatemanager.h"

Material::Material(std::string name)
	: m_diffuse(GamestateManager::instance->getTextureManager().createTexture(name + "_diffuse"))
	, m_specular(GamestateManager::instance->getTextureManager().createTexture(name + "_specular"))
	, m_shader(GamestateManager::instance->getShaderManager().createShader("test"))
{
	m_shader->set("diffuse", 0);
	m_shader->set("specular", 1);
}

void Material::enable(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	GamestateManager::instance->getTextureManager().bindTexture(0, m_diffuse);
	GamestateManager::instance->getTextureManager().bindTexture(1, m_specular);
	GamestateManager::instance->getShaderManager().useShader(m_shader);
	glm::mat4 mvp = projection * view * model;
	m_shader->set("mmodel", model);
	m_shader->set("mview", view);
	m_shader->set("mprojection", projection);
	m_shader->set("mmvp", mvp);
}
