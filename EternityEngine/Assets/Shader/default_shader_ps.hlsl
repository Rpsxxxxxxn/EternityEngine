static const float BIAS = 0.0001f;

Texture2D textureDiffuse : register(t0);
Texture2D depthMapTexture : register(t1);

SamplerState samLinear : register(s0);
SamplerState samWrap : register(s1);

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

struct PS_IN
{
	float4 position		: SV_POSITION;
	float3 color		: COLOR0;
	float3 normal		: NORMAL;
	float2 tex			: TEXCOORD0;
	float4 lightViewPos : TEXCOORD1;
	float3 lightPos		: TEXCOORD2;
};

float4 main(PS_IN input) : SV_Target0
{
	float4 color = 1.0f;

	float2 texCoord;
	texCoord.x =  input.lightViewPos.x / input.lightViewPos.w / 2.0f + 0.5f;
	texCoord.y = -input.lightViewPos.y / input.lightViewPos.w / 2.0f + 0.5f;

	if ((saturate(texCoord.x) == texCoord.x) &&
		(saturate(texCoord.y) == texCoord.y))
	{
		float depthValue = depthMapTexture.Sample(samWrap, texCoord).x;
		
		float lightDepthValue = input.lightViewPos.z / input.lightViewPos.w;
		
		if ((lightDepthValue - BIAS) > depthValue)
		{
			color = ambient;
		}
	}

	float4 textureColor = textureDiffuse.Sample(samLinear, input.tex);

	float3 eyeVector = normalize(camPos.xyz - input.position.xyz);

	float3 halfVector = normalize(direction + normalize(lightPosition.xyz));

	float specular = pow(max(0.0f, dot(input.normal, halfVector)), 20.0f) * 0.55f;

	float4 finalColor = (color * textureColor) + specular;

	return saturate(finalColor);
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}