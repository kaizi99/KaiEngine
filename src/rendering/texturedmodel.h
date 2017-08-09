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

#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "material.h"

class Mesh;

class TexturedModel
{
public:
	TexturedModel(Mesh* mesh, Material material);

	void render(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
private:
	Mesh* m_mesh;
	Material m_material;
};
