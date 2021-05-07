//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_BODY_H
#define SURVIVE_BODY_H


#include <glm/glm.hpp>

#include "BodyType.h"
#include "Entity.h"

namespace Survive
{
	class BoundingBox
	{
	private:
		const glm::vec3 &m_Position;
		float m_Width;
		float m_Height;

	public:
		BoundingBox(const glm::vec3 &position, float width, float height);

		static bool collide(const BoundingBox &box1, const BoundingBox &box2);
	};

	class Circle;

	class Rectangle;

	class Body
	{
	protected:
		Entity &m_Body;
		glm::vec2 m_Velocity;
		BodyType m_BodyType;

		float m_Mass;

	public:
		Body(Entity &entity2D, const BodyType &bodyType, float mass, const glm::vec2 &initialVelocity);

		virtual ~Body() = default;

		[[nodiscard]] const BodyType &bodyType() const;

		virtual void collide(Circle &circle) = 0;

		virtual void collide(Rectangle &rectangle) = 0;

		virtual void accept(Body &body) = 0;

		Entity &getBody();

		[[nodiscard]] const glm::vec2 &velocity() const;

	};

	class Circle : public Body
	{
	private:
		float m_Radius;

	public:
		explicit Circle(Entity &circle, float radius, float mass, const BodyType &bodyType,
						const glm::vec2 &initialVelocity = glm::vec2{});

		void collide(Circle &circle) override;

		void collide(Rectangle &r) override;

		void accept(Body &body) override;
	};

	class Rectangle : public Body
	{
	private:
		float m_Width, m_Height;

	public:
		Rectangle(Entity &rectangle, float width, float height, float mass, const BodyType &bodyType,
				  const glm::vec2 &initialVelocity = glm::vec2{});

		void collide(Circle &circle) override;

		void collide(Rectangle &rectangle) override;

		void accept(Body &body) override;

		[[nodiscard]] float width() const;

		[[nodiscard]] float height() const;
	};
}

#endif //SURVIVE_BODY_H
