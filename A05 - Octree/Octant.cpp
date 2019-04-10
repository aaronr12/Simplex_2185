#include "Octant.h"
#include "MyRigidBody.h"
using namespace Simplex;

Simplex::Octant::Octant(uint a_uMaxLevel, uint a_uIdealEntityCount)
{

}

Simplex::Octant::Octant(vector3 a_v3Center, vector3 a_v3HalfWidth)
{
}

Simplex::Octant::Octant(Octant const & other)
{
}

Octant & Simplex::Octant::operator=(Octant const & other)
{
	// TODO: insert return statement here
}

Simplex::Octant::~Octant(void)
{
}

void Simplex::Octant::Swap(Octant & other)
{
}

vector3 Simplex::Octant::GetHalfWidth(void)
{
	return vector3();
}

vector3 Simplex::Octant::GetCenter(void)
{
	return vector3();
}

vector3 Simplex::Octant::GetMin(void)
{
	return vector3();
}

vector3 Simplex::Octant::GetMax(void)
{
	return vector3();
}

bool Simplex::Octant::IsColliding(uint a_uRBIndex)
{
	return false;
}

void Simplex::Octant::Display(uint a_uIndex, vector3 a_v3Color)
{
}

void Simplex::Octant::Display(vector3 a_v3Color)
{
}

void Simplex::Octant::DisplayLeafs(vector3 a_v3Color)
{
}

void Simplex::Octant::ClearEntityList(void)
{
}

void Simplex::Octant::Subdivide(void)
{
}

Octant * Simplex::Octant::GetChild(uint a_uChild)
{
	return nullptr;
}

Octant * Simplex::Octant::GetParent(void)
{
	return nullptr;
}

bool Simplex::Octant::IsLeaf(void)
{
	return false;
}

bool Simplex::Octant::ContainsMoreThan(uint a_uEntities)
{
	return false;
}

void Simplex::Octant::KillBranches(void)
{
}

void Simplex::Octant::ConstructTree(void)
{
}

void Simplex::Octant::AssignIDtoEntity(void)
{
}

uint Simplex::Octant::GetOctantCount(void)
{
	return uint();
}

void Simplex::Octant::Release(void)
{
}

void Simplex::Octant::Init(void)
{

}

void Simplex::Octant::ConstructList(void)
{
}
