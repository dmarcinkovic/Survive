//
// Created by david on 06. 03. 2022..
//

#include "ObjectBehaviour.h"
#include "Components.h"

namespace Survive
{
	class Example : public ObjectBehaviour
	{
	public:
		void start() override
		{
			log("Log message");
		}

		void update() override
		{
			if (exists<Transform3DComponent>())
			{
				Transform3DComponent &transform = getComponent<Transform3DComponent>();

				if (isKeyPressed(Key::A))
				{
					transform.position.x -= 0.05f;
				} else if (isKeyPressed(Key::D))
				{
					transform.position.x += 0.05f;
				} else if (isKeyPressed(Key::W))
				{
					transform.position.y += 0.05f;
				} else if (isKeyPressed(Key::S))
				{
					transform.position.y -= 0.05f;
				}
			}
		}

		void onDestroy() override
		{
			log("Entity destroyed");
		}
	};
}

extern "C" Survive::ObjectBehaviour *create()
{
	return new Survive::Example();
}

extern "C" void destroy(Survive::ObjectBehaviour *object)
{
	delete object;
}
