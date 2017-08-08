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

#include "MeshManager.h"

#include "../mesh.h"
#include "../vertex.h"

MeshManager::MeshManager()
{

}

Mesh* MeshManager::createMesh(std::vector<Vertex> vertices, std::vector<int> indices)
{
	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(vertices, indices);
	Mesh* rawMesh = mesh.get();
	m_meshes.push_back(std::move(mesh));
	return rawMesh;
}

void MeshManager::renderMesh(Mesh* mesh)
{
	if (m_activeMesh != mesh)
	{
		m_activeMesh = mesh;
		m_activeMesh->bind();
	}

	m_activeMesh->render();
}
