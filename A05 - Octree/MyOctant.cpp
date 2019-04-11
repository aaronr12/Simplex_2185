#include "MyRigidBody.h"
#include "MyOctant.h"
using namespace Simplex;

void Simplex::MyOctant::Init(void)
{
	m_uID = 0; //Will store the current ID for this octant
	m_uLevel = 0; //Will store the current level of the octant
	m_uChildren = 0;// Number of children on the octant (either 0 or 8)

	m_v3Center = vector3(0.0f); //Will store the center point of the octant
	m_v3Min = vector3(0.0f); //Will store the minimum vector of the octant
	m_v3Max = vector3(0.0f); //Will store the maximum vector of the octant
	m_v3Halfwidth = vector3(0.0f);

	m_pParent = nullptr;// Will store the parent of current octant
	m_pChild[8];//Will store the children of the current octant
}

// big 3
Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	Init();

	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = m_uIdealEntityCount;

	std::vector<vector3> points;

	MyRigidBody* currentRigidBody = new MyRigidBody(points);

	m_v3Max = currentRigidBody->GetMaxGlobal;
	m_v3Min = currentRigidBody->GetMinGlobal;
	m_v3Center = currentRigidBody->GetCenterGlobal;
}

Simplex::MyOctant::MyOctant(vector3 a_v3Center, vector3 a_v3Halfwidth)
{
	Init();

	m_v3Center = a_v3Center;
	m_v3Min = a_v3Center - a_v3Halfwidth;
	m_v3Max = a_v3Center + a_v3Halfwidth;
}

Simplex::MyOctant::MyOctant(MyOctant const & other)
{
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_uChildren = other.m_uChildren;
	m_pMeshMngr = other.m_pMeshMngr;
	m_pEntityMngr = other.m_pEntityMngr;
	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
	m_pParent = other.m_pParent;
	*m_pChild = *other.m_pChild;
	m_pRoot = other.m_pRoot;
	m_lChild = other.m_lChild;
}

MyOctant & Simplex::MyOctant::operator=(MyOctant const & other)
{
	// TODO: insert return statement here
	Release();
	Init();
	MyOctant temp(other);
	Swap(temp);
	return *this;
}

Simplex::MyOctant::~MyOctant(void)
{
	Release();
}

void Simplex::MyOctant::Swap(MyOctant & other)
{
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_uChildren, other.m_uChildren);
	std::swap(m_pMeshMngr, other.m_pMeshMngr);
	std::swap(m_pEntityMngr, other.m_pEntityMngr);
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
	std::swap(m_pParent, other.m_pParent);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);
}

float Simplex::MyOctant::GetSize(void)
{
	return 0.0f;
}

vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return vector3();
}

vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return vector3();
}

vector3 Simplex::MyOctant::GetMaxGlobal(void)
{
	return vector3();
}

bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
{

	return false;
}

void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
{
	if (m_uID == a_nIndex)
	{
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(m_v3Halfwidth * 2.0f), a_v3Color);
	}
	else
	{
		if (m_uChildren > 0)
		{
			for (size_t i = 0; i < m_uChildren; i++)
			{
				m_pChild[i]->Display(a_nIndex, a_v3Color);
			}
		}
	}
}

void Simplex::MyOctant::Display(vector3 a_v3Color)
{
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(m_v3Halfwidth * 2.0f), a_v3Color);
	if (m_uChildren > 0)
	{
		for (size_t i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->Display(a_v3Color);
		}
	}
}

void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
{
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(m_v3Halfwidth * 2.0f), a_v3Color);
	if (m_uChildren > 0)
	{
		for (size_t i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->Display(a_v3Color);
		}
	}
}

void Simplex::MyOctant::ClearEntityList(void)
{
	if (m_uChildren > 0)
	{
		for (size_t i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->ClearEntityList();
		}
	}
	m_EntityList.clear();
}

void Simplex::MyOctant::Subdivide(void)
{
	if (m_uLevel >= m_uMaxLevel || !ContainsMoreThan(m_uIdealEntityCount))
	{
		m_uChildren = 8;

		vector3 v3ChildHalfWidth = m_v3Halfwidth / 2.0f;

		// calculate min, max, and center for children
		vector3 v3ChildCenter;

		// top front left
		v3ChildCenter = m_v3Center + vector3(-v3ChildHalfWidth.x, v3ChildHalfWidth.y, v3ChildHalfWidth.z);
		m_pChild[1] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[1]->m_uID = this->m_uID + 1;

		// top front right
		v3ChildCenter = m_v3Center + v3ChildHalfWidth;
		m_pChild[0] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[0]->m_uID = this->m_uID + 2;

		// bottom front left
		v3ChildCenter = m_v3Center + vector3(-v3ChildHalfWidth.x, -v3ChildHalfWidth.y, v3ChildHalfWidth.z);
		m_pChild[3] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[3]->m_uID = this->m_uID + 3;

		// bottom front right
		v3ChildCenter = m_v3Center + vector3(v3ChildHalfWidth.x, -v3ChildHalfWidth.y, v3ChildHalfWidth.z);
		m_pChild[2] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[2]->m_uID = this->m_uID + 4;

		// top back left
		v3ChildCenter = m_v3Center + vector3(-v3ChildHalfWidth.x, v3ChildHalfWidth.y, -v3ChildHalfWidth.z);
		m_pChild[5] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[5]->m_uID = this->m_uID + 5;

		// top back right
		v3ChildCenter = m_v3Center + vector3(v3ChildHalfWidth.x, v3ChildHalfWidth.y, -v3ChildHalfWidth.z);
		m_pChild[4] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[4]->m_uID = this->m_uID + 6;

		// bottom back left
		v3ChildCenter = m_v3Center + vector3(-v3ChildHalfWidth.x, -v3ChildHalfWidth.y, -v3ChildHalfWidth.z);
		m_pChild[7] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[7]->m_uID = this->m_uID + 7;

		// bottom back right
		v3ChildCenter = m_v3Center + vector3(v3ChildHalfWidth.x, -v3ChildHalfWidth.y, -v3ChildHalfWidth.z);
		m_pChild[6] = new MyOctant(v3ChildCenter, v3ChildHalfWidth);
		m_pChild[6]->m_uID = this->m_uID + 8;
	}
}

MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
{
	return nullptr;
}

MyOctant * Simplex::MyOctant::GetParent(void)
{
	return nullptr;
}

bool Simplex::MyOctant::IsLeaf(void)
{
	return m_uChildren;
}

bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
{
	return m_EntityList.size() > a_nEntities;
}

void Simplex::MyOctant::KillBranches(void)
{

}

void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
{
	if (m_uID == 0 && m_uOctantCount == 1)
	{
		ClearEntityList();
		AssignIDtoEntity();
		Subdivide();
	}
}

void Simplex::MyOctant::AssignIDtoEntity(void)
{
}

uint Simplex::MyOctant::GetOctantCount(void)
{
	return uint();
}

void Simplex::MyOctant::Release(void)
{
}

void Simplex::MyOctant::ConstructList(void)
{
}
