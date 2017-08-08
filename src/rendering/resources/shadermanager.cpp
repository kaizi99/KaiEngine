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

#include "shadermanager.h"

ShaderManager::ShaderManager()
{

}

Shader* ShaderManager::createShader(std::string name)
{
	//auto pair = m_existingShaders.find(name);
	//if (pair != m_existingShaders.end())
	//	return pair->second;

	std::unique_ptr<Shader> shader = std::make_unique<Shader>(name);
	Shader* rawShader = shader.get();
	m_shaders.push_back(std::move(shader));
	//m_existingShaders[name] = shader.get();
	return rawShader;
}

void ShaderManager::useShader(Shader* shader)
{
	if (m_activeShader != shader)
	{
		m_activeShader = shader;
		m_activeShader->enable();
	}
}
