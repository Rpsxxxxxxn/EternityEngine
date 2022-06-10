Texture2D textureDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;

	float4 camPos;
};

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

struct VS_IN
{
	float4 position : POSITION0;
	float3 normal	: NORMAL0;
	float4 color	: COLOR0;
	float2 tex		: TEXCOORD0;
};

struct VS_OUT
{
	float4 position		: SV_POSITION;
	float3 color		: COLOR0;
	float3 normal		: NORMAL;
	float2 tex			: TEXCOORD0;
	float4 lightViewPos : TEXCOORD1;
	float3 lightPos		: TEXCOORD2;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	float4 worldPosition;
	input.position.w = 1.0f;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	output.lightViewPos = mul(input.position, world);
	output.lightViewPos = mul(output.lightViewPos, lightView);
	output.lightViewPos = mul(output.lightViewPos, lightProj);

	output.color	= input.color;

	output.tex		= input.tex;

	output.normal	= mul(input.normal, world);
	output.normal	= normalize(output.normal);

	worldPosition = mul(input.position, world);

	output.lightPos = lightPosition.xyz - worldPosition.xyz;
	output.lightPos = normalize(output.lightPos);

	return output;
}