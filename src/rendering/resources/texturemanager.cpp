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

#include "texturemanager.h"

TextureManager::TextureManager()
{

}

Texture* TextureManager::createTexture(std::string name)
{
	//auto pair = m_existingTextures.find(name);
	//if (pair != m_existingTextures.end())
	//	return pair->second;

	std::unique_ptr<Texture> texture = std::unique_ptr<Texture>(new Texture(name));
	Texture* rawTexture = texture.get();
	m_textures.push_back(std::move(texture));
	//m_textures.push_back(std::move(texture));
	//m_existingTextures[name] = texture.get();
	return rawTexture;
}

void TextureManager::bindTexture(int textureUnit, Texture* texture)
{
	auto pair = m_boundTextures.find(textureUnit);
	if (pair == m_boundTextures.end())
	{
		m_boundTextures.insert(std::make_pair(textureUnit, texture));
		texture->bind(textureUnit);
	}
	else if (pair->second != texture)
	{
		m_boundTextures.insert(std::make_pair(textureUnit, texture));
		texture->bind(textureUnit);
	}
	else
		texture->bind(textureUnit);
}
