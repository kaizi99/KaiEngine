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

#include <glm/glm.hpp>

#include "../core/entity.h"

#include "texturedmodel.h"
#include "camera.h"

class ModelEntity : public Entity
{
public:
	ModelEntity(TexturedModel model, Camera& camera, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

	void update();
	void render();

	void setCamera(Camera& camera);
private:
	TexturedModel m_model;
	Camera m_camera;

	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};
