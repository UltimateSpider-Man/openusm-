#include "../standardConstants.h"

struct VS_in
{
	float4 Position		: POSITION;
	float3 Normal		: NORMAL;
	float2 TexCoord		: TEXCOORD0;
	int4 Indices        : BLENDINDICES;
	float4 Weights      : BLENDWEIGHT;
	
};

struct VS_out {
	float4 Position		: POSITION;
	float2 TexCoord0	: TEXCOORD0;
	float2 TexCoord1	: TEXCOORD1;
};

float4x4 MVP : register(c0);


float4x3 Bones[24] : register(c11);

float2 c90 : register(c90);
float4 c91 : register(c91);

VS_out main(in VS_in input)
{
	VS_out output;

    const int4 bones = input.Indices;
    
    float4x3 skinTransform = Bones[bones.x] * input.Weights.x;
    skinTransform += Bones[bones.y] * input.Weights.y;
    skinTransform += Bones[bones.z] * input.Weights.z;
    skinTransform += Bones[bones.w] * input.Weights.w;
    
    float3 position = mul(input.Position, skinTransform);
    
    float4 r4;
    r4.xyz = position;
    
    float3 normal = mul(input.Normal, (float3x3)skinTransform);
    
    float3 r5 = normal;
    
    float r6 = dot(r5.xyzz, r5.xyzz);
    
    r6 = 1.0 / sqrt(abs(r6));
    
    r5.xyz = r5.xyzz * r6;
    
    r4.w = c91.z;
      
    float4 r7;
    r7.xyz = r4;
    r7.w = c91.z;
    
    output.Position = mul(r4, MVP);
    
	output.TexCoord0 = input.TexCoord;
	
	output.TexCoord1.xy = input.Normal;
	

	return output;
}
