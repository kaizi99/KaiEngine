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

#include <unordered_map>
#include <utility>

struct GLFWwindow;

enum ButtonState
{
	KEY_JUST_PRESSED,
	KEY_PRESSED,
	KEY_RELEASED
};

class Input
{
public:
	Input();
	static Input* instance;

	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void update();

	ButtonState getKeyState(int key);
	std::pair<double, double> getMouseDelta();

private:
	std::pair<double, double> m_pos;
    std::pair<double, double> m_oldPos;

    bool m_firstMouse;

	std::unordered_map<int, ButtonState> m_buttons;
};
