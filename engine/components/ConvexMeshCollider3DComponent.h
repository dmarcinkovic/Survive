//
// Created by david on 27. 01. 2022..
//

#ifndef SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENT_H
#define SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>
#include <vector>

#include "Collider3DComponent.h"

namespace Survive
{
	struct ConvexMeshCollider3DComponent : public Collider3DComponent
	{
	public:
		std::vector<float> vertices;
		std::vector<int> indices;

		int numberOfFaces{};

	private:
		friend class PhysicSystem;

		using VertexType = rp3d::PolygonVertexArray::VertexDataType;
		using IndexType = rp3d::PolygonVertexArray::IndexDataType;

		static constexpr VertexType VERTEX_TYPE = VertexType::VERTEX_FLOAT_TYPE;
		static constexpr IndexType INDEX_TYPE = IndexType::INDEX_INTEGER_TYPE;

		std::vector<rp3d::PolygonVertexArray::PolygonFace> polygonFaces;
		rp3d::PolygonVertexArray *polygonVertexArray{};
		rp3d::PolyhedronMesh *polyhedronMesh{};

		rp3d::ConvexMeshShape *meshShape{};

	public:
		ConvexMeshCollider3DComponent() = default;

		ConvexMeshCollider3DComponent(std::vector<float> meshVertices, std::vector<int> meshIndices, int numberOfFaces)
				: vertices(std::move(meshVertices)), indices(std::move(meshIndices)),
				  numberOfFaces(numberOfFaces)
		{
		}
	};
}

#endif //SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENT_H
