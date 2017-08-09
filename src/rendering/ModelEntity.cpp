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

#include "ModelEntity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "texturedmodel.h"

#include "../core/gamestate/gamestatemanager.h"

ModelEntity::ModelEntity(TexturedModel model, Camera* camera, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
	: m_model(model)
	, m_pos(pos)
	, m_rot(rot)
	, m_scale(scale)
	, m_camera(camera)
{
}

void ModelEntity::update()
{

}

void ModelEntity::render()
{
	glm::mat4 translation = glm::translate(glm::mat4(), m_pos);
	//TODO: Rotation
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scale = glm::scale(m_scale);

	glm::mat4 model = translation * rotation * scale;
	m_model.render(model, m_camera->getView(), m_camera->getProjection());
}

void ModelEntity::setCamera(Camera* camera)
{
	m_camera = camera;
}
