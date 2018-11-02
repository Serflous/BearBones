#pragma once

#include "ModelBase.h"

namespace Objects
{
	/**
	 * A simple geometric model.
	 * @author
	 * @version 0.1
	 */
	class PrimitiveModel : public ModelBase
	{
	public:
		PrimitiveModel();
		PrimitiveModel(const PrimitiveModel & other);
		~PrimitiveModel();

		/**
		 * Sets the colour of the model.
		 * @param[in] The colour to change the model to.
		 */
		void SetColour(glm::vec3 colour);
		/**
		 * Gets the colour of the model.
		 * @return The colour of the model.
		 */
		glm::vec3 GetColour();

	private:
		glm::vec3 m_colour;
	};

}