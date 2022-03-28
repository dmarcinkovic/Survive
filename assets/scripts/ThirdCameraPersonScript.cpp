//
// Created by david on 28. 03. 2022..
//

#include "ObjectBehaviour.h"
#include "Components.h"

namespace Survive
{
	class ThirdCameraPersonScript : public ObjectBehaviour
	{
	public:

		void update() override
		{

		}
	};
}

extern "C" Survive::ObjectBehaviour *create()
{
	return new Survive::ThirdCameraPersonScript();
}

extern "C" void destroy(Survive::ObjectBehaviour *object)
{
	delete object;
}