#pragma once

#include <vector>

#include "GUITexture.h"

namespace Objects
{
	/**
	 * The GUI of the program.
	 * @author Mathew Causby
	 * @version 0.1
	 */
	class GUI
	{

	public:
		GUI();
		GUI(const GUI & other);
		~GUI();

		/**
		 * Adds a texture to use in the GUI.
		 * @param[in] texture The texture to add.
		 */
		void AddTexture(std::shared_ptr<Objects::GUITexture> texture);

		/**
		 * Gets the textures for use in the GUI.
		 * @return The textures that have been added.
		 */
		std::vector<std::shared_ptr<GUITexture>> GetTextures();

	private:
		std::vector<std::shared_ptr<GUITexture>> m_textures;

	};

}