#include "GUI.h"

Objects::GUI::GUI()
{
	
}

Objects::GUI::GUI(const GUI & other)
{
	m_textures = other.m_textures;
}

Objects::GUI::~GUI()
{

}

void Objects::GUI::AddTexture(std::shared_ptr<Objects::GUITexture> texture)
{
	m_textures.push_back(texture);
}

std::vector<std::shared_ptr<Objects::GUITexture>> Objects::GUI::GetTextures()
{
	return m_textures;
}