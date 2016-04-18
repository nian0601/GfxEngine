#include "stdafx.h"

#include "Instance.h"
#include "Scene.h"

namespace Frost
{
	Scene::Scene()
		: myCamera(nullptr)
		, myInstances(16)
	{
	}


	Scene::~Scene()
	{
	}

	void Scene::Render()
	{
		DL_ASSERT_EXP(myCamera != nullptr, "Cant render without a Camera");

		for (Instance* instance : myInstances)
		{
			instance->Render(*myCamera);
		}
	}

	void Scene::SetCamera(Camera& aCamera)
	{
		myCamera = &aCamera;
	}

	void Scene::AddInstance(Instance* aInstance)
	{
		myInstances.Add(aInstance);
	}

	void Scene::RemoveInstance(Instance* aInstance)
	{
		DL_ASSERT_EXP(myInstances.Find(aInstance) != myInstances.FoundNone, "Cant remove Instance thats not in the scene");
		myInstances.RemoveCyclic(aInstance);
	}

}