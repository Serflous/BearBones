#pragma once

#include "Texture.h"

#include <memory>
#include <GLM/vec2.hpp>

namespace Objects
{

	class GUITexture
	{
	public:
		GUITexture();
		GUITexture(const GUITexture & other);
		~GUITexture();

		void SetTextue(std::shared_ptr<Objects::Texture> texture);
		void SetPosition(glm::vec2 position);
		void SetSize(glm::vec2 size);

		std::shared_ptr<Objects::Texture> GetTexture();
		glm::vec2 GetPosition();
		glm::vec2 GetSize();

	private:
		std::shared_ptr<Objects::Texture> m_texture;
		glm::vec2 m_position;
		glm::vec2 m_size;
	};

}