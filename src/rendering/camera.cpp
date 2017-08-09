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

#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../core/gamestate/gamestatemanager.h"

#define PI 3.14159265359

Camera::Camera(glm::vec3 pos, glm::vec3 rot)
	:	m_pos(pos)
	,	m_rot(rot)
{
	computeMatrecies();
}

void Camera::update(double deltaTime)
{
    Input& input = GamestateManager::instance->getInput();

    ButtonState state = input.getKeyState(GLFW_KEY_W);
    if (state == KEY_JUST_PRESSED || state == KEY_PRESSED)
        m_pos += m_cameraSpeed * (float)deltaTime * m_front;

    state = input.getKeyState(GLFW_KEY_S);
    if (state == KEY_JUST_PRESSED || state == KEY_PRESSED)
        m_pos -= m_cameraSpeed * (float)deltaTime * m_front;

    state = input.getKeyState(GLFW_KEY_A);
    if (state == KEY_JUST_PRESSED || state == KEY_PRESSED)
        m_pos -= m_cameraSpeed * (float)deltaTime * m_right;

    state = input.getKeyState(GLFW_KEY_D);
    if (state == KEY_JUST_PRESSED || state == KEY_PRESSED)
        m_pos += m_cameraSpeed * (float)deltaTime * m_right;

    computeMatrecies();
}

glm::mat4 Camera::getView()
{
	return m_view;
}

glm::mat4 Camera::getProjection()
{
	return m_projection;
}

void Camera::move(glm::vec3 delta)
{
	m_pos += delta;
	computeMatrecies();
}

void Camera::rotate(glm::vec3 delta)
{
	m_rot += delta;

	if (m_rot.x > 90.0f)
		m_rot.x = 90.0f;

	if (m_rot.x < -90.0f)
		m_rot.x = -90.0f;

	computeMatrecies();
}

void Camera::setPosition(glm::vec3 pos)
{
	m_pos = pos;
	computeMatrecies();
}

void Camera::setRotation(glm::vec3 rot)
{
	m_rot = rot;
	computeMatrecies();
}

void Camera::computeMatrecies()
{
	float verticalAngle = glm::radians(m_rot.x);
	float horizontalAngle = glm::radians(m_rot.y);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin((horizontalAngle)-PI / 2.0f),
		0,
		cos(horizontalAngle - PI / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

    m_front = direction;
    m_right = right;

	m_view = glm::lookAt(m_pos, m_pos + direction, up);
	m_projection = glm::perspective(glm::radians(70.0f), GamestateManager::instance->getAspectRatio(), 0.01f, 1000.0f);
}
