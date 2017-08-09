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

class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 rot);

	glm::mat4 getView();
	glm::mat4 getProjection();

	void update(double deltaTime);

	void move(glm::vec3 delta);
	void rotate(glm::vec3 delta);

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
private:
	glm::mat4 m_view;
	glm::mat4 m_projection;

	glm::vec3 m_pos;
	glm::vec3 m_rot;

    glm::vec3 m_front;
    glm::vec3 m_right;

    float m_cameraSpeed = 1.0f;
    float m_sensitivity = 0.85f;

	void computeMatrecies();
};
