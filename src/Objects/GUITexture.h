#pragma once

#include "Texture.h"

#include <memory>
#include <GLM/vec2.hpp>

namespace Objects
{
		/**
		 * A texture to be used in the GUI.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class GUITexture
	{
	public:
		GUITexture();
		GUITexture(const GUITexture & other);
		~GUITexture();

			/**
			 * Sets the texture to use.
			 * @param[in] texture The texture to use.
			 */
		void SetTextue(std::shared_ptr<Objects::Texture> texture);
			/**
			 * Sets the position of the texture.
			 * @param[in] The position to place the texture at.
			 */
		void SetPosition(glm::vec2 position);
			/**
			 * Sets the size of the texure.
			 * @param[in] The size to set the texture to.
			 */
		void SetSize(glm::vec2 size);

			/**
			 * Gets the texture.
			 * @return The texture.
			 */
		std::shared_ptr<Objects::Texture> GetTexture();
			/**
			 * Gets the position of the texture.
			 * @return The position of the texture.
			 */
		glm::vec2 GetPosition();
			/**
			 * Gets the size of the texture.
			 * @return The size of the texture.
			 */
		glm::vec2 GetSize();

	private:
		std::shared_ptr<Objects::Texture> m_texture;
		glm::vec2 m_position;
		glm::vec2 m_size;
	};

}