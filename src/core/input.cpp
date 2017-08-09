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

#include "input.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include "gamestate/gamestatemanager.h"

Input* Input::instance;

Input::Input()
{
    instance = this;
    m_firstMouse = true;
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (instance->m_firstMouse)
    {
        instance->m_oldPos = std::make_pair(xpos, ypos);
        instance->m_firstMouse = false;
    }
    else
        instance->m_oldPos = instance->m_pos;

    instance->m_pos = std::make_pair(xpos, ypos);
}

void Input::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
        GamestateManager::instance->closeWindow();

    if (action == GLFW_REPEAT)
        return;

    auto pair = instance->m_buttons.find(key);
    if (pair == instance->m_buttons.end())
    {
        instance->m_buttons.insert(std::make_pair(key, KEY_JUST_PRESSED));
        return;
    }

    if (action == GLFW_PRESS)
        instance->m_buttons[key] = KEY_JUST_PRESSED;

    if (action == GLFW_RELEASE)
        instance->m_buttons[key] = KEY_RELEASED;
}

void Input::update()
{
    std::vector<int> toChange;

    for (auto it : m_buttons)
        if (it.second == KEY_JUST_PRESSED)
            toChange.push_back(it.first);

    for (int it : toChange)
        m_buttons[it] = KEY_PRESSED;
}

ButtonState Input::getKeyState(int key)
{
	auto pair = m_buttons.find(key);
    if (pair == m_buttons.end())
        return KEY_RELEASED;

    return pair->second;
}

std::pair<double, double> Input::getMouseDelta()
{
	return std::make_pair(m_oldPos.first - m_pos.first, m_oldPos.second - m_pos.second);
}
