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
	private:
		using VertexType = rp3d::PolygonVertexArray::VertexDataType;
		using IndexType = rp3d::PolygonVertexArray::IndexDataType;

		static constexpr VertexType VERTEX_TYPE = VertexType::VERTEX_FLOAT_TYPE;
		static constexpr IndexType INDEX_TYPE = IndexType::INDEX_INTEGER_TYPE;

		std::vector<float> vertices;
		std::vector<int> indices;

	public:
		std::vector<rp3d::PolygonVertexArray::PolygonFace> polygonFaces;
		rp3d::PolygonVertexArray *polygonVertexArray{};
		rp3d::PolyhedronMesh *polyhedronMesh{};

		ConvexMeshCollider3DComponent() = default;

		ConvexMeshCollider3DComponent(std::vector<float> meshVertices, std::vector<int> meshIndices, int numberOfFaces,
									  int numberOfVertices)
				: vertices(std::move(meshVertices)), indices(std::move(meshIndices)), polygonFaces(numberOfFaces)
		{
			int numberOfVerticesInFace = static_cast<int>(indices.size()) / numberOfFaces;

			for (int face = 0; face < numberOfFaces; ++face)
			{
				polygonFaces[face].indexBase = face * numberOfVerticesInFace;
				polygonFaces[face].nbVertices = numberOfVerticesInFace;
			}

			std::size_t verticesStride = (vertices.size() / numberOfVertices) * sizeof(float);
			polygonVertexArray = new rp3d::PolygonVertexArray(numberOfVertices, vertices.data(),
															  static_cast<int>(verticesStride), indices.data(),
															  sizeof(int), numberOfFaces, polygonFaces.data(),
															  VERTEX_TYPE, INDEX_TYPE);
		}
	};
}

#endif //SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENT_H
