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

void Survive::ComponentSerializer::saveRigidBodyComponent(entt::registry &registry, entt::entity entity,
														  std::ofstream &writer)
{
	if (registry.any_of<MaterialComponent>(entity))
	{
		const MaterialComponent &rigidBodyComponent = registry.get<MaterialComponent>(entity);

		writer << "\tcomponent:MaterialComponent\n";
		writer << "\t\tisTransparent:" << rigidBodyComponent.isTransparent << '\n';
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

void Survive::ComponentSerializer::printVec3(std::ofstream &writer, const char *label, const glm::vec3 &vec3)
{
	writer << "\t\t" << label << ':' << vec3.x << ',' << vec3.y << ',' << vec3.z << '\n';
}

void Survive::ComponentSerializer::printVec4(std::ofstream &writer, const char *label, const glm::vec4 &vec4)
{
	writer << "\t\t" << label << ':' << vec4.x << ',' << vec4.y << ',' << vec4.z << ',' << vec4.w << '\n';
}

void
Survive::ComponentSerializer::saveTextComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer)
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
