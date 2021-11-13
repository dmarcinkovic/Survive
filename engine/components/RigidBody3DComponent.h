//
// Created by david on 09. 11. 2021..
//

#ifndef SURVIVE_RIGIDBODY3DCOMPONENT_H
#define SURVIVE_RIGIDBODY3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

namespace Survive
{
	struct RigidBody3DComponent
	{
		rp3d::RigidBody *body{};

		rp3d::BodyType bodyType = rp3d::BodyType::STATIC;
		float mass{};
		bool useGravity = true;
		float linearDamping{};
		rp3d::Vector3 linearVelocity = rp3d::Vector3{0.0f, 0.0f, 0.0f};
		float angularDrag{};

		RigidBody3DComponent() = default;

		RigidBody3DComponent(rp3d::BodyType bodyType, float mass, bool useGravity = true, float linearDamping = 0.0f,
							 const rp3d::Vector3 &linearVelocity = rp3d::Vector3{0.0f, 0.0f, 0.0f},
							 float angularDrag = 0.0f)
				: bodyType(bodyType), mass(mass), linearDamping(linearDamping),
				  linearVelocity(linearVelocity), angularDrag(angularDrag), useGravity(useGravity)
		{
		}
	};
}

#endif //SURVIVE_RIGIDBODY3DCOMPONENT_H
