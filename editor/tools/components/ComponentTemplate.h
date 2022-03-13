//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTEMPLATE_H
#define SURVIVE_COMPONENTTEMPLATE_H

namespace Survive
{
	template<class ComponentType>
	class ComponentTemplate
	{
	public:
		void drawComponent(ComponentType &component, bool *)
		{}
	};
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
