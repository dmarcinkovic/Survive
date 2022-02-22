//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTEMPLATE_H
#define SURVIVE_COMPONENTTEMPLATE_H

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "DaeParser.h"
#include "AudioMaster.h"
#include "ObjParser.h"
#include "Components.h"
#include "EditorUtil.h"
#include "OpenDialog.h"
#include "Loader.h"
#include "Log.h"

namespace Survive
{
	class ComponentTemplate
	{
	private:
		AudioMaster m_AudioMaster;
		OpenDialog m_OpenDialog;
		Loader m_Loader;

		EditorUtil m_EditorUtil;

		bool m_IsUsingKeyEvents{};

	public:
		template<typename ComponentType>
		void drawComponent(ComponentType &component, bool * = nullptr)
		{}

		[[nodiscard]] bool isUsingKeyEvents() const
		{
			return m_IsUsingKeyEvents;
		}
	};

	template<>
	inline void ComponentTemplate::drawComponent(Transform3DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Transform3D", visible))
		{
			ImGui::Columns(4);
			EditorUtil::drawTransform3DHeader();

			ImGui::Text("Position");
			EditorUtil::drawTransform3DRow(component.position, "##PosX", "##PosY", "##PosZ");
			ImGui::Text("Rotation");
			EditorUtil::drawTransform3DRow(component.rotation, "##RotX", "##RotY", "##RotZ");
			ImGui::Text("Scale");
			EditorUtil::drawTransform3DRow(component.scale, "##ScX", "##ScY", "##ScZ", 0.0f);

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(Render3DComponent &component, bool *visible)
	{
		static bool changed = true;
		static bool dialogTextureOpen = false;
		static bool dialogModelOpen = false;

		if (ImGui::CollapsingHeader("Render3D", visible))
		{
			TexturedModel &texturedModel = component.texturedModel;

			ImGui::PushID("Render3D component");
			ImGui::Columns(2);

			m_EditorUtil.loadModel(m_OpenDialog, texturedModel.getModel(), component.modelName, changed,
								   dialogModelOpen);
			ImGui::NextColumn();
			m_EditorUtil.loadTexture(m_OpenDialog, texturedModel.getTexture(), component.textureName,
									 "Texture: %s", "Load texture", changed, dialogTextureOpen);

			ImGui::Columns();
			ImGui::PopID();

			if (changed && texturedModel.isValidTexture() && texturedModel.isValidModel())
			{
				changed = false;
			}
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(MaterialComponent &component, bool *visible)
	{
		static bool changed = true;
		static bool open = false;

		if (ImGui::CollapsingHeader("Material", visible))
		{
			ImGui::Checkbox("Transparent", &component.isTransparent);

			ImGui::Separator();

			ImGui::Checkbox("Use normal mapping", &component.useNormalMapping);

			ImGui::PushID("Material component");
			ImGui::Columns(2);
			m_EditorUtil.loadTexture(m_OpenDialog, component.normalMap, component.normalMapPath,
									 "Normal map: %s", "Load texture", changed, open);

			ImGui::Columns();
			ImGui::PopID();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(ShadowComponent &component, bool *visible)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.65f, 0.6f, 0.6f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.5f, 0.55f, 0.5f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));

		if (ImGui::CollapsingHeader("Shadow", visible))
		{
			ImGui::Checkbox("Add shadow", &component.loadShadow);
		}

		ImGui::PopStyleColor(3);
	}

	template<>
	inline void ComponentTemplate::drawComponent(BloomComponent &component, bool *visible)
	{
		static bool changed = true;
		static bool open = false;

		if (ImGui::CollapsingHeader("Bloom", visible))
		{
			ImGui::Columns(2, nullptr, false);
			EditorUtil::drawColumnDragFloat("Bloom strength", "##Bloom strength", component.bloomStrength, 0, 5, 0.1f);

			ImGui::Separator();

			ImGui::PushID("Bloom component");
			ImGui::Columns(2);
			m_EditorUtil.loadTexture(m_OpenDialog, component.emissiveTexture, component.textureName,
									 "Texture: %s", "Load texture", changed, open);
			ImGui::Columns();
			ImGui::PopID();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(ReflectionComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Reflection", visible))
		{
			ImGui::Columns(2, nullptr, false);
			EditorUtil::drawColumnDragFloat("Reflection factor", "##Reflection factor",
											component.reflectionFactor, 0, 1, 0.1f);
			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(RefractionComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Refraction", visible))
		{
			ImGui::Columns(2, nullptr, false);
			EditorUtil::drawColumnDragFloat("Refraction index", "##RIndex", component.refractiveIndex, 0, 3, 0.1f);
			EditorUtil::drawColumnDragFloat("Refraction factor", "##RFactor", component.refractiveFactor, 0, 1, 0.1f);
			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(Render2DComponent &component, bool *visible)
	{
		static bool changed = true;
		static bool open = false;

		if (ImGui::CollapsingHeader("Render2D", visible))
		{
			TexturedModel &texturedModel = component.texturedModel;

			ImGui::PushID("Render 2D Component");
			ImGui::Columns(2);
			m_EditorUtil.loadTexture(m_OpenDialog, texturedModel.getTexture(), component.textureName,
									 "Texture: %s", "Load texture", changed, open);
			EditorUtil::loadQuadModel(changed, texturedModel, m_Loader);

			ImGui::Columns();
			ImGui::PopID();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(SoundComponent &component, bool *visible)
	{
		static bool changed = true;
		static bool open = false;

		if (ImGui::CollapsingHeader("Sound", visible))
		{
			ImGui::Columns(2, nullptr, false);
			if (EditorUtil::drawColumnDragFloat("Pitch", "##Pitch", component.pitch, 0.0f, 5.0f, 0.1f))
			{
				component.audioSource.setPitch(component.pitch);
			}

			if (EditorUtil::drawColumnDragFloat("Gain", "##Gain", component.gain, 0.0f, 5.0f, 0.1f))
			{
				component.audioSource.setGain(component.gain);
			}

			EditorUtil::drawColumnInputBool("Play on loop", "##LoopSound", component.playOnLoop);
			ImGui::Separator();

			ImGui::Columns(2);

			m_EditorUtil.loadSound(m_OpenDialog, m_AudioMaster, component.sound, component.soundFile, changed, open);
			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(SpriteComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Sprite", visible))
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(TextComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Text", visible))
		{
			ImGui::Text("Text");
			Text &text = component.text;

			m_IsUsingKeyEvents = EditorUtil::drawTextInput(text, text.m_Text, m_Loader);
			m_EditorUtil.chooseFont(m_OpenDialog, component, text.m_Font);

			EditorUtil::chooseFontSpacing(text.m_LineSpacing, text, m_Loader);

			if (ImGui::Checkbox("Center string", &text.m_Centered) &&
				!text.m_Text.empty() && text.m_Font.isFontLoaded())
			{
				text.loadTexture(m_Loader);
			}

			ImGui::Columns();

			EditorUtil::loadFontBorder(text.m_AddBorder, text.m_BorderWidth, text.m_BorderColor);
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(SpriteSheetComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Sprite sheet", visible))
		{
			ImGui::Columns(2, nullptr, false);

			EditorUtil::drawColumnInputInt("Number of rows", "##Number of rows", component.row);
			EditorUtil::drawColumnInputInt("Number of columns", "##Number of columns", component.col);
			ImGui::Separator();
			EditorUtil::drawColumnInputInt("Start index", "##Start index", component.startIndex);
			EditorUtil::drawColumnInputInt("End index", "##End index", component.endIndex);
			ImGui::Separator();
			EditorUtil::drawColumnInputInt("Sprites in second", "##NSprites", component.spritesInSecond);
			EditorUtil::drawColumnInputInt("Number of epochs", "##NEpochs", component.numberOfEpochs);
			ImGui::Separator();

			EditorUtil::drawColumnInputBool("Animate", "##Animate sprites", component.animating);

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(Collider2DComponent &component, bool *)
	{
		b2FixtureDef &fixtureDef = component.fixtureDef;

		EditorUtil::drawColumnInputFloat("Mass", "##Box mass", fixtureDef.density, 0.0f);
		EditorUtil::drawColumnDragFloat("Friction", "##Box friction", fixtureDef.friction, 0, 1, 0.05f);
		EditorUtil::drawColumnInputFloat("Elasticity", "##Box restitution", fixtureDef.restitution, 0.0f, 1.0f);
	}

	template<>
	inline void ComponentTemplate::drawComponent(BoxCollider2DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Box collider 2D", visible))
		{
			ImGui::Columns(2, nullptr, false);

			if (EditorUtil::drawColumnDragFloat("Width", "##Box width", component.width))
			{
				component.boxShape.SetAsBox(component.width, component.height, component.center, 0);
				component.m_Initialized = true;
			}

			if (EditorUtil::drawColumnDragFloat("Height", "##Box height", component.height))
			{
				component.boxShape.SetAsBox(component.width, component.height, component.center, 0);
				component.m_Initialized = true;
			}

			b2Vec2 oldCenter = component.center;
			if (EditorUtil::drawColumnDragFloat2("Center", "##Box center", component.center))
			{
				EditorUtil::moveBoxCenter(component.boxShape.m_vertices, component.center - oldCenter);
			}

			ImGui::PushID("Box2D");
			drawComponent<Collider2DComponent>(component, nullptr);
			ImGui::PopID();

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(CircleCollider2DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Circle collider 2D", visible))
		{
			ImGui::Columns(2, nullptr, false);

			if (EditorUtil::drawColumnDragFloat("Radius", "##Cicle radius", component.circleShape.m_radius))
			{
				component.m_Initialized = true;
			}

			EditorUtil::drawColumnDragFloat2("Center", "##Circle center", component.circleShape.m_p);

			ImGui::PushID("Circle2D");
			drawComponent<Collider2DComponent>(component, nullptr);
			ImGui::PopID();

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(EdgeCollider2DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Edge collider 2D", visible))
		{
			ImGui::Columns(2, nullptr, false);

			if (EditorUtil::drawColumnDragFloat2("First point", "##Edge p1", component.edgeShape.m_vertex1))
			{
				component.m_Initialized = true;
			}

			if (EditorUtil::drawColumnDragFloat2("Second point", "##Edge p2", component.edgeShape.m_vertex2))
			{
				component.m_Initialized = true;
			}

			ImGui::PushID("Edge2D");
			drawComponent<Collider2DComponent>(component, nullptr);
			ImGui::PopID();

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(PolygonCollider2DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Polygon collider 2D", visible))
		{
			EditorUtil::addPolygonPoint(component.points, component.polygonShape);

			ImGui::Columns(2, nullptr, false);

			m_EditorUtil.drawPolygonPoints(component.points, component.polygonShape);

			ImGui::Separator();

			ImGui::PushID("Polygon2D");
			drawComponent<Collider2DComponent>(component, nullptr);
			ImGui::PopID();

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(RigidBody2DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Rigid body 2D", visible))
		{
			static const char *bodyTypes[] = {"Static", "Kinematic", "Dynamic"};

			b2BodyDef &bodyDef = component.bodyDefinition;

			int currentItem = bodyDef.type;
			if (ImGui::Combo("Body type", &currentItem, bodyTypes, 3))
			{
				bodyDef.type = static_cast<b2BodyType>(currentItem);
			}

			ImGui::Separator();
			ImGui::Columns(2, nullptr, false);

			EditorUtil::drawColumnInputFloat("Linear drag", "##Linear drag", bodyDef.linearDamping, 0.0f);
			EditorUtil::drawColumnInputFloat("Angular drag", "##Angular drag", bodyDef.angularDamping, 0.0f);
			EditorUtil::drawColumnInputFloat("Gravity scale", "##Gravity scale", bodyDef.gravityScale);

			EditorUtil::drawColumnDragFloat2("Linear velocity", "##Linear velocity", bodyDef.linearVelocity);
			EditorUtil::drawColumnInputBool("Fixed angle", "##Fixed angle", bodyDef.fixedRotation);

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(HingeJoint2DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Hinge joint 2D", visible))
		{
			ImGui::Columns(2, nullptr, false);

			b2RevoluteJointDef &jointDef = component.jointDef;

			EditorUtil::drawColumnInputText("##HingeBody", "Connected Rigid Body", component.connectedBodyName);
			EditorUtil::initializeDragDropTarget(component.connectedBody, component.connectedBodyName);

			ImGui::NextColumn();

			EditorUtil::drawColumnDragFloat2("Anchor", "##HingeAnchorA", jointDef.localAnchorA);
			EditorUtil::drawColumnDragFloat2("Connected anchor", "##HingeAnchorB", jointDef.localAnchorB);
			EditorUtil::drawColumnInputBool("Collide connected", "##HingeCollide", jointDef.collideConnected);

			ImGui::Separator();
			EditorUtil::drawHingeMotorProperties(component);

			ImGui::Separator();
			EditorUtil::drawHingeAngleProperties(component);

			ImGui::Columns();
		}
	}

	template<>
	inline void ComponentTemplate::drawComponent(DistanceJoint2DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Distance joint 2D", visible))
		{
			ImGui::Columns(2, nullptr, false);

			EditorUtil::drawColumnInputText("##DistanceBody", "Connected Rigid Body", component.connectedBodyName);
			EditorUtil::initializeDragDropTarget(component.connectedBody, component.connectedBodyName);

			ImGui::NextColumn();

			b2DistanceJointDef &jointDef = component.jointDef;

			EditorUtil::drawColumnDragFloat2("Anchor", "##DistanceAnchorA", jointDef.localAnchorA);
			EditorUtil::drawColumnDragFloat2("Connected anchor", "##DistanceAnchorB", jointDef.localAnchorB);
			EditorUtil::drawColumnInputBool("Collide connected", "##DistanceCollide", jointDef.collideConnected);

			ImGui::Separator();

			EditorUtil::drawColumnDragFloat("Min length", "##DistanceJointMinLen", jointDef.minLength);
			EditorUtil::drawColumnDragFloat("Max length", "##DistanceJointMaxLen", jointDef.maxLength);

			ImGui::Columns();
		}
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
