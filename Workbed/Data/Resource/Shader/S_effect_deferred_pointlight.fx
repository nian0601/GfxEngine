#include "S_u_variables.fx"

struct PointLightData
{
	float4 Position;
	float4 Color;
	float Range;
};
PointLightData PointLight[1];

Pixel_LightMesh VertexShader_PointLight(Vertex_LightMesh aInput)
{
	Pixel_LightMesh output = (Pixel_LightMesh)0;

	float range = 10.f;//PointLight[0].Range;
	float4 scale = float4(range, range, range, 1.0f);
	aInput.Position *= scale;
	
	aInput.Position.w = 1.0f;

	Matrix mat = mul(World, ViewProjection);
	output.Position = mul(aInput.Position, mat);

	float x = output.Position.x;
	float y = output.Position.y;
	float w = output.Position.w;

	output.Tex = float4((float2(x + w, w - y)) / 2, output.Position.zw);

	return output;
}

float4 PixelShader_PointLight(Pixel_LightMesh aInput) : SV_Target
{
	return PointLight[0].Color;
	aInput.Tex /= aInput.Tex.w;

	PBLData data = CalculatePBLData_GBuffer(aInput.Tex.xy);

	float3 viewPos = CameraPosition;
	float3 toEye = normalize(viewPos - data.WorldPosition.xyz);

	float3 toLight = PointLight[0].Position - data.WorldPosition;
	float3 lightDir = normalize(toLight);
	float3 halfVec = normalize(lightDir + toEye.xyz);
	float NdotL = saturate(dot(data.Normal.xyz, lightDir));
	float HdotN = saturate(dot(halfVec, data.Normal.xyz));
	float NdotV = saturate(dot(data.Normal.xyz, toEye));

	float3 F = saturate(Fresnel(data.Substance.xyz, lightDir, halfVec));
	float D = saturate(D_GGX(HdotN, (data.Roughness + 1.f) / 2.f));
	float V = saturate(SchlickForGGX((data.Roughness + 1.f) / 2.f, NdotV, NdotL));
	float lambert = NdotL;

	float attenuation = Attenuation(toLight, PointLight[0].Range);
	float3 lightColor = PointLight[0].Color.xyz * 10 * attenuation;
	float3 directSpecc = F * D * V * NdotL * lightColor;
	return float4(directSpecc, 1.f);
	//return float4(1, 1, 1, 1);
	/*
	PBLData data = CalculatePBLData_GBuffer(aInput.Tex);
	
	float3 ToEye = normalize(CameraPosition - data.WorldPosition.xyz);
	float3 RefFresnel = ReflectionFresnel(data.Substance, data.Normal, ToEye, 1 - data.RoughnessOffsetted);


	//Calculate the AmbientDiffuse, this is simply the Cubemap * AmbientOcclusion * MetalnessAlbedo
	//we also multiply with (1 - RefFresnel) to keep us energy conserving (Dont want to create more light than we receive)
	float3 ambientDiffuse = Cubemap.SampleLevel(linearSampling, data.Normal, 7).xyz * data.AmbientOcclusion * data.MetalnessAlbedo * (1 - RefFresnel);


	//Next we need to calculate the AmbientSpecc
	float3 ReflectionVector = reflect(ToEye, data.Normal);
	float LysMipLevel = GetLysMipLevel(data.Roughness, 10);

	float3 ambientSpecc = Cubemap.SampleLevel(linearSampling, ReflectionVector, LysMipLevel).xyz * data.AmbientOcclusion * RefFresnel;

	float3 ambientColor = saturate(ambientDiffuse + ambientSpecc);



	//To test things we also do calculations for a faked directional light
	float3 LightDir = normalize(float3(-0.5f, 1.f, 1.f));
	float3 LightColor = float3(0.f, 1.f, 0.f);

	float3 LightHalfVec = normalize(LightDir + -ToEye);

	float NdotL = saturate(dot(data.Normal, LightDir));
	float HdotN = saturate(dot(LightHalfVec, data.Normal));

	float3 F = saturate(Fresnel(data.Substance, LightDir, LightHalfVec));
	float D = saturate(D_GGX(HdotN, (data.Roughness + 1) / 2));
	float V = saturate(SchlickForGGX((data.Roughness + 1) / 2, dot(data.Normal, ToEye), NdotL));

	float3 LightSpecc = (((D * V * F) / 3.14159 + (1 - F) * NdotL * data.MetalnessAlbedo * data.AmbientOcclusion)) * LightColor;

	return saturate(float4(ambientColor + LightSpecc, 1.f));
	*/
}

technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VertexShader_PointLight()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PixelShader_PointLight()));
	}
}
