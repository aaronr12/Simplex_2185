#pragma once

#include "MyEntityManager.h"

namespace Simplex
{
	class Octant
	{
	public:
		Octant();
		~Octant();
	private:
		float halfwidth;
		float size;
		int children = 0;
		const int maxChildren = 8;

		MeshManager* m_pMeshMngr = nullptr;
		MyEntityManager* m_pEntityMngr = nullptr;

		vector3 center = vector3(0.0f);
		vector3 localMin = vector3(0.0f);
		vector3 localMax = vector3(0.0f);

		Octant* parent = nullptr;
		Octant* child[8];

		std::vector<uint> entityList;

		Octant* root = nullptr;
		std::vector<Octant*> children;
	};

}

