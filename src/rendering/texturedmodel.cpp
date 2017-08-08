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

TexturedModel::TexturedModel(Mesh* mesh, Material material)
	: m_mesh(mesh)
	, m_material(material)
{

}

void TexturedModel::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	m_material.enable(model, view, projection);
	GamestateManager::instance->getMeshManager().renderMesh(m_mesh);
}
