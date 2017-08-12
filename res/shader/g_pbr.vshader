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

#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 mmodel;
uniform mat4 mview;
uniform mat4 mprojection;
uniform mat4 mmvp;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;

void main()
{
    gl_Position = mmvp * vec4(pos, 1.0);
    FragPos = m_model * pos;
    Normal = normal;
    TexCoord = texCoord;
}
