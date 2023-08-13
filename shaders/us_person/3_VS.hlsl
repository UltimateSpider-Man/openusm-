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

#if ID == 3
	float4 Color0		: COLOR0;
#endif
};

float4x4 MVP : register(c0);

float2 c4 : register(c4);
float2 c5 : register(c5);
float3 c6 : register(c6);
float4 c7 : register(c7);
float4 c8 : register(c8);

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
    
#if ID == 3
    float3 normal = mul(input.Normal, (float3x3)skinTransform);
#else
    float3 normal = float3(1, 0, 0);
#endif
    
    float3 r5 = normal;
    
    float r6 = dot(r5.xyzz, r5.xyzz);
    
    r6 = 1.0 / sqrt(abs(r6));
    
    r5.xyz = r5.xyzz * r6;
    
    r4.w = c91.z;
      
    float4 r7;
    r7.xyz = r4;
    r7.w = c91.z;
    
    output.Position = mul(r4, MVP);
    
    
	output.TexCoord0.xy = input.TexCoord;
	
	float4 r8;
	r8.xyz = r5;
	r8.w = c91.z;
	
	output.TexCoord1.x = dot(r8, c4);
	output.TexCoord1.y = mul(r8, c5);

#if ID == 3	
	float r9 = dot(r5, c6);
	r9 = max(r9, c91.x);
	r9 = min(r9, c91.z);
	float4 r10 = c7 * r9;
	
	output.Color0 = r10 + c8;
#endif

	return output;
}
