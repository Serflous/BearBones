#pragma once

#include "ModelBase.h"

namespace Objects
{

	class PrimitiveModel : public ModelBase
	{
	public:
		PrimitiveModel();
		PrimitiveModel(const PrimitiveModel & other);
		~PrimitiveModel();

		void SetColour(glm::vec3 colour);
		glm::vec3 GetColour();

	private:
		glm::vec3 m_colour;
	};

}