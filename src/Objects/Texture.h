#pragma once

#include <GL/glut.h>

namespace Objects
{

	class Texture
	{
	public:
		Texture();
		Texture(const Texture & other);
		~Texture();

		void Bind();
		void Unbind();
		void Destroy();
		void SetTextureID(int texId);
		int GetTextureID();

	private:
		GLuint m_textureId;
	};

}