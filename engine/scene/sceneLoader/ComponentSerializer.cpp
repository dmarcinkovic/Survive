//
// Created by david on 18. 07. 2021..
//

#include "Components.h"
#include "ComponentSerializer.h"

void Survive::ComponentSerializer::saveAnimationComponent(entt::registry &registry, entt::entity entity,
														  std::ofstream &writer)
{
	if (registry.any_of<AnimationComponent>(entity))
	{
		writer << "\tcomponent:AnimationComponent\n";
	}
}

void
Survive::ComponentSerializer::saveBloomComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer)
{
	if (registry.any_of<BloomComponent>(entity))
	{
		const BloomComponent &bloomComponent = registry.get<BloomComponent>(entity);

		writer << "\tcomponent:BloomComponent\n";
		writer << "\t\ttextureName:" << bloomComponent.textureName << '\n';
		writer << "\t\tbloomStrength:" << bloomComponent.bloomStrength << '\n';
	}
}

void Survive::ComponentSerializer::saveReflectionComponent(entt::registry &registry, entt::entity entity,
														   std::ofstream &writer)
{
	if (registry.any_of<ReflectionComponent>(entity))
	{
		const ReflectionComponent &reflectionComponent = registry.get<ReflectionComponent>(entity);

		writer << "\tcomponent:ReflectionComponent\n";
		writer << "\t\treflectionFactor:" << reflectionComponent.reflectionFactor << '\n';
	}
}

void Survive::ComponentSerializer::saveRefractionComponent(entt::registry &registry, entt::entity entity,
														   std::ofstream &writer)
{
	if (registry.any_of<RefractionComponent>(entity))
	{
		const RefractionComponent &refractionComponent = registry.get<RefractionComponent>(entity);

		writer << "\tcomponent:RefractionComponent\n";
		writer << "\t\trefractiveIndex:" << refractionComponent.refractiveIndex << '\n';
		writer << "\t\trefractiveFactor:" << refractionComponent.refractiveFactor << '\n';
	}
}

void Survive::ComponentSerializer::saveRender2DComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.any_of<Render2DComponent>(entity))
	{
		const Render2DComponent &renderComponent = registry.get<Render2DComponent>(entity);

		writer << "\tcomponent:Render2DComponent\n";
		writer << "\t\ttextureName:" << renderComponent.textureName << '\n';
	}
}

void Survive::ComponentSerializer::saveRender3DComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.any_of<Render3DComponent>(entity))
	{
		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(entity);

		writer << "\tcomponent:Render3DComponent\n";
		writer << "\t\tmodelName:" << renderComponent.modelName << '\n';
		writer << "\t\ttextureName:" << renderComponent.textureName << '\n';
	}
}

void Survive::ComponentSerializer::saveMaterialComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.any_of<MaterialComponent>(entity))
	{
		const MaterialComponent &rigidBodyComponent = registry.get<MaterialComponent>(entity);

		writer << "\tcomponent:MaterialComponent\n";
		writer << "\t\tisTransparent:" << rigidBodyComponent.isTransparent << '\n';
		writer << "\t\tuseNormalMapping:" << rigidBodyComponent.useNormalMapping << '\n';
		writer << "\t\tnormalMap:" << rigidBodyComponent.normalMapPath << '\n';
	}
}

void Survive::ComponentSerializer::saveShadowComponent(entt::registry &registry,
													   entt::entity entity, std::ofstream &writer)
{
	if (registry.any_of<ShadowComponent>(entity))
	{
		const ShadowComponent &shadowComponent = registry.get<ShadowComponent>(entity);

		writer << "\tcomponent:ShadowComponent\n";
		writer << "\t\tloadShadow:" << shadowComponent.loadShadow << '\n';
	}
}

void Survive::ComponentSerializer::saveSoundComponent(entt::registry &registry,
													  entt::entity entity, std::ofstream &writer)
{
	if (registry.any_of<SoundComponent>(entity))
	{
		const SoundComponent &soundComponent = registry.get<SoundComponent>(entity);

		writer << "\tcomponent:SoundComponent\n";
		writer << "\t\tsoundFile:" << soundComponent.soundFile << '\n';
		writer << "\t\tpitch:" << soundComponent.pitch << '\n';
		writer << "\t\tgain:" << soundComponent.gain << '\n';
		writer << "\t\tplayOnLoop:" << soundComponent.playOnLoop << '\n';
		writer << "\t\tplay:" << soundComponent.play << '\n';
	}
}

void
Survive::ComponentSerializer::saveSpriteComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer)
{
	if (registry.any_of<SpriteComponent>(entity))
	{
		const SpriteComponent &spriteComponent = registry.get<SpriteComponent>(entity);

		writer << "\tcomponent:SpriteComponent\n";
		printVec4(writer, "color", spriteComponent.color);
	}
}

void Survive::ComponentSerializer::saveSpriteSheetComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.any_of<SpriteSheetComponent>(entity))
	{
		const SpriteSheetComponent &component = registry.get<SpriteSheetComponent>(entity);

		writer << "\tcomponent:SpriteSheetComponent\n";
		writer << "\t\trows:" << component.row << '\n';
		writer << "\t\tcols:" << component.col << '\n';
		writer << "\t\tstartIndex:" << component.startIndex << '\n';
		writer << "\t\tendIndex:" << component.endIndex << '\n';
		writer << "\t\tspritesInSecond:" << component.spritesInSecond << '\n';
		writer << "\t\tnumberOfEpochs:" << component.numberOfEpochs << '\n';
		writer << "\t\tanimate:" << component.animating << '\n';
	}
}

void Survive::ComponentSerializer::saveTransform3DComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.any_of<Transform3DComponent>(entity))
	{
		const Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(entity);

		writer << "\tcomponent:Transform3DComponent\n";

		printVec3(writer, "position", transformComponent.position);
		printVec3(writer, "scale", transformComponent.scale);
		printVec3(writer, "rotation", transformComponent.rotation);
	}
}

void Survive::ComponentSerializer::saveBoxCollider2DComponent(entt::registry &registry, entt::entity entity,
															  std::ofstream &writer)
{
	if (registry.any_of<BoxCollider2DComponent>(entity))
	{
		const BoxCollider2DComponent &boxCollider = registry.get<BoxCollider2DComponent>(entity);

		writer << "\tcomponent:BoxCollider2DComponent\n";
		writer << "\t\twidth:" << boxCollider.width << '\n';
		writer << "\t\theight:" << boxCollider.height << '\n';
		printVec2(writer, "center", boxCollider.center);

		saveCollider2DComponent(writer, boxCollider);
	}
}

void Survive::ComponentSerializer::saveCircleCollider2DComponent(entt::registry &registry, entt::entity entity,
																 std::ofstream &writer)
{
	if (registry.any_of<CircleCollider2DComponent>(entity))
	{
		const CircleCollider2DComponent &circleCollider = registry.get<CircleCollider2DComponent>(entity);

		writer << "\tcomponent:CircleCollider2DComponent\n";
		writer << "\t\tradius:" << circleCollider.circleShape.m_radius << '\n';
		printVec2(writer, "center", circleCollider.circleShape.m_p);

		saveCollider2DComponent(writer, circleCollider);
	}
}

void Survive::ComponentSerializer::saveEdgeCollider2DComponent(entt::registry &registry, entt::entity entity,
															   std::ofstream &writer)
{
	if (registry.any_of<EdgeCollider2DComponent>(entity))
	{
		const EdgeCollider2DComponent &edgeCollider = registry.get<EdgeCollider2DComponent>(entity);

		writer << "\tcomponent:EdgeCollider2DComponent\n";
		printVec2(writer, "point1", edgeCollider.edgeShape.m_vertex1);
		printVec2(writer, "point2", edgeCollider.edgeShape.m_vertex2);

		saveCollider2DComponent(writer, edgeCollider);
	}
}

void Survive::ComponentSerializer::savePolygonCollider2DComponent(entt::registry &registry, entt::entity entity,
																  std::ofstream &writer)
{
	if (registry.any_of<PolygonCollider2DComponent>(entity))
	{
		const PolygonCollider2DComponent &polygonCollider = registry.get<PolygonCollider2DComponent>(entity);

		writer << "\tcomponent:PolygonCollider2DComponent\n";

		const std::vector<b2Vec2> &points = polygonCollider.points;

		writer << "\t\tnumberOfPoints:" << points.size() << '\n';

		for (int i = 0; i < points.size(); ++i)
		{
			std::string name = "point" + std::to_string(i + 1);
			printVec2(writer, name.c_str(), points[i]);
		}

		saveCollider2DComponent(writer, polygonCollider);
	}
}

void Survive::ComponentSerializer::saveHingeJoint2DComponent(entt::registry &registry, entt::entity entity,
															 std::ofstream &writer)
{
	if (registry.any_of<HingeJoint2DComponent>(entity))
	{
		const HingeJoint2DComponent &hingeComponent = registry.get<HingeJoint2DComponent>(entity);

		writer << "\tcomponent:HingeJoint2DComponent\n";
		writer << "\t\tconnectedBody:" << hingeComponent.connectedBodyName << '\n';

		const b2RevoluteJointDef &jointDef = hingeComponent.jointDef;
		printVec2(writer, "anchorA", jointDef.localAnchorA);
		printVec2(writer, "anchorB", jointDef.localAnchorB);

		writer << "\t\tcollideConnected:" << jointDef.collideConnected << '\n';

		writer << "\t\tuseMotor:" << jointDef.enableMotor << '\n';
		writer << "\t\tmotorSpeed:" << jointDef.motorSpeed << '\n';
		writer << "\t\tmaxTorque:" << jointDef.maxMotorTorque << '\n';

		writer << "\t\tenableLimit:" << jointDef.enableLimit << '\n';
		writer << "\t\tlowerAngle:" << jointDef.lowerAngle << '\n';
		writer << "\t\tupperAngle:" << jointDef.upperAngle << '\n';
	}
}

void Survive::ComponentSerializer::saveDistanceJoint2DComponent(entt::registry &registry, entt::entity entity,
																std::ofstream &writer)
{
	if (registry.any_of<DistanceJoint2DComponent>(entity))
	{
		const DistanceJoint2DComponent &distanceJointComponent = registry.get<DistanceJoint2DComponent>(entity);

		writer << "\tcomponent:DistanceJoint2DComponent\n";
		writer << "\t\tconnectedBody:" << distanceJointComponent.connectedBodyName << '\n';

		const b2DistanceJointDef &jointDef = distanceJointComponent.jointDef;
		printVec2(writer, "anchorA", jointDef.localAnchorA);
		printVec2(writer, "anchorB", jointDef.localAnchorB);

		writer << "\t\tcollideConnected:" << jointDef.collideConnected << '\n';

		writer << "\t\tminLength:" << jointDef.minLength << '\n';
		writer << "\t\tmaxLength:" << jointDef.maxLength << '\n';
	}
}

void Survive::ComponentSerializer::saveRigidBody2DComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.any_of<RigidBody2DComponent>(entity))
	{
		const RigidBody2DComponent &rigidBody = registry.get<RigidBody2DComponent>(entity);

		writer << "\tcomponent:RigidBody2DComponent\n";

		const b2BodyDef &bodyDef = rigidBody.bodyDefinition;
		writer << "\t\tbodyType:" << static_cast<int>(bodyDef.type) << '\n';

		writer << "\t\tlinearDrag:" << bodyDef.linearDamping << '\n';
		printVec2(writer, "linearVelocity", bodyDef.linearVelocity);
		writer << "\t\tangularDrag:" << bodyDef.angularDamping << '\n';

		writer << "\t\tgravityScale:" << bodyDef.gravityScale << '\n';
		writer << "\t\tfixedAngle:" << bodyDef.fixedRotation << '\n';
	}
}

void Survive::ComponentSerializer::saveTextComponent(entt::registry &registry, entt::entity entity,
													 std::ofstream &writer)
{
	if (registry.any_of<TextComponent>(entity))
	{
		const TextComponent &textComponent = registry.get<TextComponent>(entity);
		const Text &text = textComponent.text;

		writer << "\tcomponent:TextComponent\n";
		writer << "\t\ttext:" << text.m_Text << '\n';
		writer << "\t\tfontFile:" << textComponent.fontFile << '\n';
		writer << "\t\ttextureAtlas:" << textComponent.textureAtlas << '\n';
		writer << "\t\tlineSpacing:" << text.m_LineSpacing << '\n';
		writer << "\t\tcenterText:" << text.m_Centered << '\n';
		writer << "\t\taddBorder:" << text.m_AddBorder << '\n';
		writer << "\t\tborderWidth:" << text.m_BorderWidth << '\n';
		printVec3(writer, "borderColor", text.m_BorderColor);
	}
}

void Survive::ComponentSerializer::saveRigidBody3DComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.any_of<RigidBody3DComponent>(entity))
	{
		const RigidBody3DComponent &rigidBody = registry.get<RigidBody3DComponent>(entity);
		writer << "\tcomponent:RigidBody3DComponent\n";

		writer << "\t\tbodyType:" << static_cast<int>(rigidBody.bodyType) << '\n';
		writer << "\t\tmass:" << rigidBody.mass << '\n';
		writer << "\t\tuseGravity:" << rigidBody.useGravity << '\n';
		writer << "\t\tlinearDamping:" << rigidBody.linearDamping << '\n';
		printVec3(writer, "linearVelocity", rigidBody.linearVelocity);
		writer << "\t\tangularDrag:" << rigidBody.angularDrag << '\n';
	}
}

void Survive::ComponentSerializer::saveBoxCollider3DComponent(entt::registry &registry, entt::entity entity,
															  std::ofstream &writer)
{
	if (registry.any_of<BoxCollider3DComponent>(entity))
	{
		const BoxCollider3DComponent &boxCollider = registry.get<BoxCollider3DComponent>(entity);
		writer << "\tcomponent:BoxCollider3DComponent\n";

		printVec3(writer, "position", boxCollider.position);
		printVec3(writer, "center", boxCollider.center);
		writer << "\t\tbounciness:" << boxCollider.bounciness << '\n';
		writer << "\t\tfriction:" << boxCollider.friction << '\n';
	}
}

void Survive::ComponentSerializer::saveCapsuleCollider3DComponent(entt::registry &registry, entt::entity &entity,
																  std::ofstream &writer)
{
	if (registry.any_of<CapsuleCollider3DComponent>(entity))
	{
		const CapsuleCollider3DComponent &capsuleCollider = registry.get<CapsuleCollider3DComponent>(entity);
		writer << "\tcomponent:CapsuleCollider3DComponent\n";

		printVec3(writer, "center", capsuleCollider.center);
		writer << "\t\tradius:" << capsuleCollider.radius << '\n';
		writer << "\t\theight:" << capsuleCollider.height << '\n';
		writer << "\t\tbounciness:" << capsuleCollider.bounciness << '\n';
		writer << "\t\tfriction:" << capsuleCollider.friction << '\n';
	}
}

void Survive::ComponentSerializer::saveSphereCollider3DComponent(entt::registry &registry, entt::entity &entity,
																 std::ofstream &writer)
{
	if (registry.any_of<SphereCollider3DComponent>(entity))
	{
		const SphereCollider3DComponent &sphereCollider = registry.get<SphereCollider3DComponent>(entity);
		writer << "\tcomponent:SphereCollider3DComponent\n";

		writer << "\t\tradius:" << sphereCollider.radius << '\n';
		printVec3(writer, "offset", sphereCollider.offset);
		writer << "\t\tbounciness:" << sphereCollider.bounciness << '\n';
		writer << "\t\tfriction:" << sphereCollider.friction << '\n';
	}
}

void Survive::ComponentSerializer::saveConvexMeshCollider3DComponent(entt::registry &registry, entt::entity &entity,
																	 std::ofstream &writer)
{
	if (registry.any_of<ConvexMeshCollider3DComponent>(entity))
	{
		const ConvexMeshCollider3DComponent &convexMesh = registry.get<ConvexMeshCollider3DComponent>(entity);
		writer << "\tcomponent:ConvexMeshCollider3DComponent\n";
		writer << "\t\tnumberOfFaces:" << convexMesh.numberOfFaces << '\n';

		const std::vector<float> &vertices = convexMesh.vertices;
		writer << "\t\tnumberOfVertices:" << vertices.size() << '\n';

		for (int i = 0; i < vertices.size(); ++i)
		{
			std::string label = "\t\tvertex" + std::to_string(i + 1);
			writer << label << ':' << vertices[i] << '\n';
		}

		const std::vector<int> &indices = convexMesh.indices;
		writer << "\t\tnumberOfIndices:" << indices.size() << '\n';

		for (int i = 0; i < indices.size(); ++i)
		{
			std::string label = "\t\tindex" + std::to_string(i + 1);
			writer << label << ':' << indices[i] << '\n';
		}

		writer << "\t\tbounciness:" << convexMesh.bounciness << '\n';
		writer << "\t\tfriction:" << convexMesh.friction << '\n';
	}
}

void Survive::ComponentSerializer::saveOutlineComponent(entt::registry &registry, entt::entity entity,
														std::ofstream &writer)
{
	if (registry.any_of<OutlineComponent>(entity))
	{
		writer << "\tcomponent:OutlineComponent\n";
		writer << "\t\tdrawOutline:0\n";
	}
}

void Survive::ComponentSerializer::printVec3(std::ofstream &writer, const char *label, const glm::vec3 &vec3)
{
	writer << "\t\t" << label << ':' << vec3.x << ',' << vec3.y << ',' << vec3.z << '\n';
}

void Survive::ComponentSerializer::printVec4(std::ofstream &writer, const char *label, const glm::vec4 &vec4)
{
	writer << "\t\t" << label << ':' << vec4.x << ',' << vec4.y << ',' << vec4.z << ',' << vec4.w << '\n';
}

void Survive::ComponentSerializer::printVec2(std::ofstream &writer, const char *label, const b2Vec2 &vec2)
{
	writer << "\t\t" << label << ':' << vec2.x << ',' << vec2.y << '\n';
}

void Survive::ComponentSerializer::saveCollider2DComponent(std::ofstream &writer,
														   const Collider2DComponent &colliderComponent)
{
	const b2FixtureDef &fixtureDef = colliderComponent.fixtureDef;
	writer << "\t\tmass:" << fixtureDef.density << '\n';
	writer << "\t\tfriction:" << fixtureDef.friction << '\n';
	writer << "\t\telasticity:" << fixtureDef.restitution << '\n';
}

void Survive::ComponentSerializer::printVec3(std::ofstream &writer, const char *label, const rp3d::Vector3 &vec3)
{
	glm::vec3 vec{vec3.x, vec3.y, vec3.z};
	printVec3(writer, label, vec);
}

void Survive::ComponentSerializer::saveHingeJoint3DComponent(entt::registry &registry, entt::entity entity,
															 std::ofstream &writer)
{
	if (registry.any_of<HingeJoint3DComponent>(entity))
	{
		HingeJoint3DComponent &hingeJoint = registry.get<HingeJoint3DComponent>(entity);
		writer << "\tcomponent:HingeJoint3DComponent\n";

		rp3d::HingeJointInfo &info = hingeJoint.jointInfo;
		saveJoint3DComponent(writer, hingeJoint.connectedBodyName, info.isCollisionEnabled,
							 info.isUsingLocalSpaceAnchors, info.anchorPointWorldSpace, info.anchorPointBody1LocalSpace,
							 info.anchorPointBody2LocalSpace);

		printVec3(writer, "axis", info.rotationAxisWorld);
		printVec3(writer, "localAxis", info.rotationAxisBody1Local);
		printVec3(writer, "axisBody2", info.rotationAxisBody2Local);

		writer << "\t\tuseMotor:" << info.isMotorEnabled << '\n';
		writer << "\t\tmotorSpeed:" << info.motorSpeed << '\n';
		writer << "\t\tmaxTorque:" << info.maxMotorTorque << '\n';

		writer << "\t\tuseLimits:" << info.isLimitEnabled << '\n';
		writer << "\t\tminAngle:" << info.minAngleLimit << '\n';
		writer << "\t\tmaxAngle:" << info.maxAngleLimit << '\n';
	}
}

void Survive::ComponentSerializer::saveCharacterJoint3DComponent(entt::registry &registry, entt::entity entity,
																 std::ofstream &writer)
{
	if (registry.any_of<CharacterJoint3DComponent>(entity))
	{
		CharacterJoint3DComponent &characterJoint = registry.get<CharacterJoint3DComponent>(entity);
		writer << "\tcomponent:CharacterJoint3DComponent\n";

		rp3d::BallAndSocketJointInfo &info = characterJoint.jointInfo;
		saveJoint3DComponent(writer, characterJoint.connectedBodyName, info.isCollisionEnabled,
							 info.isUsingLocalSpaceAnchors, info.anchorPointWorldSpace, info.anchorPointBody1LocalSpace,
							 info.anchorPointBody2LocalSpace);
	}
}

void Survive::ComponentSerializer::saveFixedJoint3DComponent(entt::registry &registry, entt::entity entity,
															 std::ofstream &writer)
{
	if (registry.any_of<FixedJoint3DComponent>(entity))
	{
		FixedJoint3DComponent &fixedJoint = registry.get<FixedJoint3DComponent>(entity);
		writer << "\tcomponent:FixedJoint3DComponent\n";

		rp3d::FixedJointInfo &info = fixedJoint.jointInfo;
		saveJoint3DComponent(writer, fixedJoint.connectedBodyName, info.isCollisionEnabled,
							 info.isUsingLocalSpaceAnchors, info.anchorPointWorldSpace, info.anchorPointBody1LocalSpace,
							 info.anchorPointBody2LocalSpace);
	}
}

void Survive::ComponentSerializer::saveJoint3DComponent(std::ofstream &writer, const std::string &connectedBodyName,
														bool enableCollision, bool isUsingLocalSpace,
														const rp3d::Vector3 &anchor, const rp3d::Vector3 &localAnchor,
														const rp3d::Vector3 &anchorBody2)
{
	writer << "\t\tconnectedBody:" << connectedBodyName << '\n';
	writer << "\t\tenableCollision:" << enableCollision << '\n';
	writer << "\t\tisUsingLocalSpace:" << isUsingLocalSpace << '\n';
	printVec3(writer, "anchor", anchor);
	printVec3(writer, "localAnchor", localAnchor);
	printVec3(writer, "anchorBody2", anchorBody2);
}

void Survive::ComponentSerializer::saveScriptComponent(entt::registry &registry, entt::entity entity,
												  std::ofstream &writer)
{
	if (registry.any_of<ScriptComponent>(entity))
	{
		writer << "\tcomponent:ScriptComponent\n";

		const ScriptComponent &script = registry.get<ScriptComponent>(entity);
		writer << "\t\tpluginLocation:" << script.pluginLocation << '\n';
	}
}

void Survive::ComponentSerializer::saveParticleComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.any_of<ParticleComponent>(entity))
	{
		const ParticleComponent &particle = registry.get<ParticleComponent>(entity);
		writer << "\tcomponent:ParticleComponent\n";

		writer << "\t\ttexturePath:" << particle.texturePath << '\n';
		writer << "\t\tparticlesPerSecond:" << particle.particlesPerSecond << '\n';
		writer << "\t\tspeed:" << particle.speed << '\n';
		writer << "\t\tgravity:" << particle.gravity << '\n';
		writer << "\t\tlifeLength:" << particle.lifeLength << '\n';

		writer << "\t\tspeedError:" << particle.speedError << '\n';
		writer << "\t\tlifeError:" << particle.lifeError << '\n';
		writer << "\t\tscaleError:" << particle.scaleError << '\n';
		writer << "\t\tdirectionDeviation:" << particle.directionDeviation << '\n';
		writer << "\t\tuseAdditiveBlending:" << particle.useAdditiveBlending << '\n';
	}
}
