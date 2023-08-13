#include "standardConstants.h"

struct VS_in
{
	float4 Position		: POSITION;
	float3 Normal       : NORMAL;
	float2 TexCoord		: TEXCOORD0;
	int4 Indices		: BLENDINDICES;
	float4 Weights		: BLENDWEIGHT;
};

struct VS_out {
	float4 Position		: POSITION;
	float2 TexCoord		: TEXCOORD0;
};


float4x4 c0 : register(c0);

float4 c9 : register(c9);

int2 c90 : register(c90);

float4 c91 : register(c91);


VS_out main(in VS_in input)
{
	VS_out output;

    const int4 r0 = input.Indices * c90.x + c90.y;

    //float4 tmp0[4] = c0;
    int i = r0.x;
    float r1 = input.Weights.x * c0[0][i];
    float r2 = input.Weights.x * c0[1][i];
    float r3 = input.Weights.x * c0[2][i];
    
    
    i = r0.y;
    r1 += input.Weights.y * c0[0][i];
    r2 += input.Weights.y * c0[1][i];
    r3 += input.Weights.y * c0[2][i];
    
    i = r0.z;
    r1 += input.Weights.z * c0[0][i];
    r2 += input.Weights.z * c0[1][i];
    r3 += input.Weights.z * c0[2][i];
    
    i = r0.w;
    r1 = input.Weights.w * c0[0][i] + r1;
    r2 = input.Weights.w * c0[1][i] + r2;
    r3 = input.Weights.w * c0[2][i] + r3;
    
    
    float4 r4;
    r4.x = dot(input.Position, r1);
    r4.y = dot(input.Position, r2);
    r4.z = dot(input.Position, r3);
  
#if 0
    float3 r5 = mul(input.Normal, float3(r1, r2, r3));
#else
    float4 r5;
    r5.x = dot(input.Normal, r1);
    r5.y = dot(input.Normal, r2);
    r5.z = dot(input.Normal, r3);
#endif
    
    //float4 r6;
    r5.w = dot(r5.xyzz, r5.xyzz);
    
    r5.w =  1.0 / sqrt(abs(r5.w)); //rsq
    
    r5.xyz = r5.xyzz * r5.w;
    
    r4.w = c91.z;
        
    r4.xyz = r5.xyzz * c9.w + r4.xyzz;

    float4 r7;
    r7.xyz = r4;
    r7.w = c91.z;

    output.Position = mul(r7, c0);
    

    output.TexCoord = input.TexCoord;

	return output;
}
