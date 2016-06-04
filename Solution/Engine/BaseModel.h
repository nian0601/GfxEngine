#pragma once

#include "EngineTypes.h"
#include <GrowingArray.h>
#include "ModelData.h"

struct D3D11_INPUT_ELEMENT_DESC;

namespace Easy3D
{
	class Effect;
	class BaseModel
	{
	public:
		BaseModel();
		virtual ~BaseModel();

		virtual void Render(Effect& aEffect);

		const ModelData& GetData() const;

	protected:
		void InitInputLayout(D3D11_INPUT_ELEMENT_DESC* aVertexDescArray, int aArraySize, EffectID aEffect);
		void InitVertexBuffer(int aVertexSize, int aBufferUsage, int aCPUUsage);
		void InitIndexBuffer();

		void SetupVertexBuffer(int aVertexCount, char* aVertexData);
		void SetupIndexBuffer(int aIndexCount, char* aIndexData);

		ModelData myData;
		CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC*> myVertexFormat;

		bool myIsNullObject;
	};

	inline const ModelData& BaseModel::GetData() const
	{
		return myData;
	}
}