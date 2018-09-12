#include "Texture.h"

Objects::Texture::Texture()
{
	m_textureId = 0;
}

Objects::Texture::Texture(const Texture & other)
{
	m_textureId = other.m_textureId;
}

Objects::Texture::~Texture()
{

}

void Objects::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Objects::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Objects::Texture::Destroy()
{
	glDeleteTextures(1, &m_textureId);
}

void Objects::Texture::SetTextureID(int texId)
{
	m_textureId = texId;
}

int Objects::Texture::GetTextureID()
{
	return m_textureId;
}