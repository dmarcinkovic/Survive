//
// Created by david on 24. 02. 2022..
//

#ifndef SURVIVE_OBJECTBEHAVIOUR_H
#define SURVIVE_OBJECTBEHAVIOUR_H

#include <sstream>

#include "entt.hpp"
#include "Key.h"
#include "Display.h"
#include "EventHandler.h"
#include "Log.h"
#include "Camera.h"

namespace Survive
{
	enum MouseButton
	{
		LeftButton = 0,
		RightButton = 1
	};

	enum MouseAction
	{
		MouseRelease = 0,
		MousePress = 1
	};

	class ObjectBehaviour
	{
	private:
		friend class ScriptingSystem;

		entt::registry *m_Registry{};
		entt::entity m_Entity = entt::null;
		EventHandler *m_EventHandler{};

		std::unordered_map<entt::entity, entt::entity> m_CopiedEntities;
		bool m_NeedRestore{};
		std::string m_Name;

		Camera *m_Camera{};

		void init(entt::registry &registry, entt::entity entity, EventHandler &eventHandler, Camera &camera);

	public:
		ObjectBehaviour() = default;

		virtual ~ObjectBehaviour() = default;

		virtual void start();

		virtual void update();

		virtual void onMouseClick(MouseButton mouseButton, MouseAction mouseAction);

		virtual void onCollisionEnter(entt::entity other);

		virtual void onCollisionExit(entt::entity other);

		virtual void onDestroy();

		virtual void onKeyboardPressed();

		virtual void onMouseScroll(float offset);

		virtual void onMouseMove();

	protected:
		template<typename ComponentType>
		decltype(auto) getComponent()
		{
			return m_Registry->get<ComponentType>(m_Entity);
		}

		template<typename ComponentType>
		decltype(auto) tryGetComponent()
		{
			return m_Registry->try_get<ComponentType>(m_Entity);
		}

		template<typename ComponentType>
		void removeComponent()
		{
			if (!m_NeedRestore)
			{
				storeEntity();
			}

			m_Registry->remove<ComponentType>(m_Entity);
		}

		template<typename ComponentType>
		bool exists()
		{
			return m_Registry->any_of<ComponentType>(m_Entity);
		}

		template<typename T, typename... Args>
		void log(T &&t, Args &&...args)
		{
			std::ostringstream ss;
			print(ss, std::forward<T>(t), std::forward<Args>(args)...);

			Log::logMessage(LogType::INFO, ss.str());
		}

		template<typename T, typename... Args>
		void logWarning(T &&t, Args &&...args)
		{
			std::ostringstream ss;
			print(ss, std::forward<T>(t), std::forward<Args>(args)...);

			Log::logMessage(LogType::WARN, ss.str());
		}

		template<typename T, typename... Args>
		void logError(T &&t, Args &&...args)
		{
			std::ostringstream ss;
			print(ss, std::forward<T>(t), std::forward<Args>(args)...);

			Log::logMessage(LogType::ERROR, ss.str());
		}

		[[nodiscard]] bool isKeyPressed(Key key) const;

		static std::pair<float, float> getMousePosition();

		static float getDeltaTime();

		[[nodiscard]] std::string getTag(entt::entity entity) const;

		static bool isMouseInsideScene();

		Camera &getCamera();

		entt::entity getEntity(const std::string &entityName) const;

	private:
		template<typename T, typename... Args>
		void print(std::ostringstream &ss, T &&t, Args &&... args)
		{
			ss << std::forward<T>(t) << ' ';

			if constexpr(sizeof...(Args) > 0)
			{
				print(ss, std::forward<Args>(args)...);
			}
		}

		void storeEntity();

		void restoreEntity();
	};
}

#endif //SURVIVE_OBJECTBEHAVIOUR_H
