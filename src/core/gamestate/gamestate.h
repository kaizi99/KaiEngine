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

class GamestateManager;

class Gamestate
{
public:
	virtual void update(double deltaTime) = 0;
	virtual void render() = 0;

	virtual void clean() = 0;

	void setGamestateManager(GamestateManager* manager)
	{
		m_manager = manager;
	}

protected:
	GamestateManager* m_manager;
};
