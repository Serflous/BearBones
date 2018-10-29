#include "GUITexture.h"

Objects::GUITexture::GUITexture()
{
	m_position = glm::vec2(0, 0);
	m_size = glm::vec2(0, 0);
	m_texture = nullptr;
}

Objects::GUITexture::GUITexture(const GUITexture & other)
{
	m_position = other.m_position;
	m_size = other.m_size;
	m_texture = other.m_texture;
}

Objects::GUITexture::~GUITexture()
{

}

void Objects::GUITexture::SetTextue(std::shared_ptr<Objects::Texture> texture)
{
	m_texture = texture;
}

void Objects::GUITexture::SetPosition(glm::vec2 position)
{
	m_position = position;
}

void Objects::GUITexture::SetSize(glm::vec2 size)
{
	m_size = size;
}

std::shared_ptr<Objects::Texture> Objects::GUITexture::GetTexture()
{
	return m_texture;
}

glm::vec2 Objects::GUITexture::GetPosition()
{
	return m_position;
}

glm::vec2 Objects::GUITexture::GetSize()
{
	return m_size;
}