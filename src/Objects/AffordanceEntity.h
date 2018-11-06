#pragma once
#include "StaticEntity.h"
namespace Objects
{
	/**
	 * An affordance of an entity.
	 * @author Mathew Causby
	 * @version 0.1
	 */
	class AffordanceEntity : public StaticEntity
	{
	public:
		AffordanceEntity();
		~AffordanceEntity();

		/**
		 * Sets the affordances for an entity.
		 * @param[in] key
		 * @param[in] value
		 */
		void SetAffordances(std::string key, double value);

		/**
		 * Sets the map of affordances for an entity.
		 * @param[in] map
		 */
		void SetAffordanceMap(std::map<std::string, double> map);

		/**
		 * Gets the affordances of an entity.
		 * @return The affordances of an entity.
		 */
		std::map<std::string, double> GetAffordances();

	private:
		std::map<std::string, double> m_affordances;
	};
}



