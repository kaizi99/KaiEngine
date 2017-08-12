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

#include "texturedmodel.h"

#include "../core/gamestate/gamestatemanager.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

TexturedModel::TexturedModel(Mesh* mesh, Texture* albedo, Texture* normal, Texture* roughness, Texture* metallic)
	: m_mesh(mesh)
	, m_albedo(albedo)
    , m_normal(normal)
    , m_roughness(roughness)
    , m_metallic(metallic)
    , m_shader(GamestateManager::instance->getShaderManager().createShader("g_pbr"))
{
    m_shader->set("albedo", 0);
    m_shader->set("normal", 1);
    m_shader->set("roughness", 2);
    m_shader->set("metallic", 3);
}

void TexturedModel::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    GamestateManager::instance->getShaderManager().useShader(m_shader);
    GamestateManager::instance->getTextureManager().bindTexture(0, m_albedo);
    GamestateManager::instance->getTextureManager().bindTexture(1, m_normal);
    GamestateManager::instance->getTextureManager().bindTexture(2, m_roughness);
    GamestateManager::instance->getTextureManager().bindTexture(3, m_metallic);

    glm::mat4 mvp = projection * view * model;
    m_shader->set("mmodel", model);
    m_shader->set("mview", view);
    m_shader->set("mprojection", projection);
    m_shader->set("mmvp", mvp);
    
	GamestateManager::instance->getMeshManager().renderMesh(m_mesh);
}
