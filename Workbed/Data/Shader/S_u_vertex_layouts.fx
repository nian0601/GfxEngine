struct VertexShader_ColoredCube
{
	float4 Position : POSITION;
	float4 Color : Color0;	
};

struct PixelShader_ColoredCube
{
	float4 Position : SV_POSITION;
	float4 Color : Color0;	
};


struct VertexShader_Model
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float2 Tex : TEXCOORD;
	float3 BiNormal : BINORMAL;
	float3 Tangent : TANGENT;
};

struct PixelShader_Model
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL;
	float2 Tex : TEXCOORD;
	float3 BiNormal : BINORMAL;
	float3 Tangent : TANGENT;
	float4 WorldPosition : POSITION;
};