// <íËêî> çsóÒ
cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;

	float4 camPos;
};

// <íËêî> ÉâÉCÉg
cbuffer LightBuffer : register(b1)
{
	float3 lightPosition;
	float3 direction;
	float4 ambient;
	float4 diffuse;

	matrix lightView;
	matrix lightProj;

	float range;
	float innerCone;
	float outerCone;
};

struct PS_IN
{
	float4 position		: SV_POSITION;
	float4 depthPosition : TEXTURE0;
};

float4 main(PS_IN input) : SV_TARGET
{
	float depth = input.depthPosition.z / input.depthPosition.w;

	return depth;
}