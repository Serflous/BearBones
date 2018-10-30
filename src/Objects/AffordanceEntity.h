#pragma once
#include "StaticEntity.h"
namespace Objects
{
	class AffordanceEntity : public StaticEntity
	{
	public:
		AffordanceEntity();
		~AffordanceEntity();

		void SetAffordances(std::string key, double value);
		void SetAffordanceMap(std::map<std::string, double> map);
		std::map<std::string, double> GetAffordances();

	private:
		std::map<std::string, double> m_affordances;
	};
}



