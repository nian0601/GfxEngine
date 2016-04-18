#include "S_u_vertex_layouts.fx"

Matrix World;
Matrix View;
Matrix Projection;
Matrix ViewProjection;
float3 CameraPosition;


Texture2D AlbedoTexture;
Texture2D NormalTexture;
Texture2D RoughnessTexture;
Texture2D MetalnessTexture;
Texture2D AOTexture;

TextureCube Cubemap;


SamplerState linearSampling
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct PBLData
{
	float3 Albedo;
	float3 MetalnessAlbedo;
	float3 Normal;
	float3 Metalness;
	float3 Substance;
	float3 AmbientOcclusion;
	float Roughness;
	float RoughnessOffsetted;
};

PBLData CalculatePBLData(float2 aTexCoord, float3 aVertexNormal, float3 aVertexBinormal, float3 aVertexTangent)
{
	PBLData output;

	output.Albedo = AlbedoTexture.Sample(linearSampling, aTexCoord);
	
	output.Metalness = MetalnessTexture.Sample(linearSampling, aTexCoord);
	output.Roughness = RoughnessTexture.Sample(linearSampling, aTexCoord);
	output.AmbientOcclusion = AOTexture.Sample(linearSampling, aTexCoord);

	output.Substance = (0.04 - 0.04 * output.Metalness) + output.Albedo * output.Metalness;
	output.MetalnessAlbedo = output.Albedo - output.Albedo * output.Metalness;

	output.RoughnessOffsetted = pow(8192, output.Roughness);

	output.Normal = NormalTexture.Sample(linearSampling, aTexCoord) * 2 - 1;
	float3x3 tangentSpaceMatrix = float3x3(normalize(aVertexTangent), normalize(aVertexBinormal), normalize(aVertexNormal));
	output.Normal = normalize(mul(output.Normal, tangentSpaceMatrix));

	return output;
}


//
//	Functions used to calculate Ambient light
//--------------------------------------------------------

//Calculates how reflections will behave in different materials
float3 ReflectionFresnel(float3 aSubstance, float3 aLightDir, float3 aHalfVector, float aRoughness)
{
	return (aSubstance + (1.f - aSubstance) * pow((1.f - saturate(dot(aLightDir, aHalfVector))), 5) / (4 - 3 * aRoughness));
}


//Calculations copied from Lys which calculates which MIP level to use for the reflections based on roughness
static const float k0 = 0.00098f;
static const float k1 = 0.9921f;
static const float fakeLysMaxSpecularPower = (2.f / (0.0014f * 0.0014f)) - 2.f;
static const float fMaxT = (exp2(-10.f / sqrt((2.f / (0.0014f * 0.0014f)) - 2.f)) - 0.00098f) / 0.9921f;

float RoughToSPow(float aRoughness)
{
	return (2.f / (aRoughness * aRoughness)) - 2.f;
}

float GetLysMipLevel(float aRoughness, int aMipCount)
{
	float fSmulMaxT = (exp2(-10.0 / sqrt(RoughToSPow(aRoughness))) - k0) / k1;

	return float(aMipCount - 1 - 0) * (1.0 - clamp(fSmulMaxT / fMaxT, 0.0, 1.0));
}



//
//	Functions used to calculate Direct light
//--------------------------------------------------------
float3 Fresnel(float3 aSubstance, float3 aLightDir, float3 aHalfVector)
{
	return (aSubstance + (1.f - aSubstance) * pow((1.f - saturate(dot(aLightDir, aHalfVector))), 5));
}

float SchlickForGGX(float aRoughness, float NdotV, float NdotL)
{
	float k = aRoughness * aRoughness * 0.5f;
	float G1V = NdotV * (1.f - k) + k;
	float G1L = NdotL * (1.f - k) + k;

	return 0.25f / (G1V * G1L);
}

float D_GGX(float HdotN, float aRoughness)
{
	float m = aRoughness * aRoughness;
	float m2 = m * m;
	float denominator = HdotN * HdotN * (m2 - 1.f) + 1.f;

	return m2 / (3.14159 * denominator * denominator);
}