#include "stdafx.h"
#include "ModelData.h"
#include "GPUData.h"

namespace Easy3D
{

	ModelData::ModelData()
		: myChildren(4)
		, myChildTransforms(4)
		, myIsNullObject(true)
		, myGPUData(nullptr)
	{

	}

	ModelData::~ModelData()
	{

	}

	void ModelData::Init(EffectID aEffectID)
	{
		if (myIsNullObject == false)
		{
			myGPUData->Init(aEffectID);
		}

		for each (ModelData* child in myChildren)
		{
			child->Init(aEffectID);
		}
	}

	void ModelData::AddChild(ModelData* aModelData)
	{
		myChildren.Add(aModelData);
		myChildTransforms.Add(aModelData->myOrientation);
	}
}