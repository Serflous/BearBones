#pragma once

#include <vector>

#include "GUITexture.h"

namespace Objects
{

	class GUI
	{

	public:
		GUI();
		GUI(const GUI & other);
		~GUI();

		void AddTexture(std::shared_ptr<Objects::GUITexture> texture);

		std::vector<std::shared_ptr<GUITexture>> GetTextures();

	private:
		std::vector<std::shared_ptr<GUITexture>> m_textures;

	};

}