#include "standardConstants.h"

struct VS_in
{
	float4 Position		: POSITION;
	float2 TexCoord		: TEXCOORD0;
	float4 Color		: COLOR0;
};

struct VS_out {
	float4 Position		: POSITION;
	float2 TexCoord0	: TEXCOORD0;
	float4 Color0		: COLOR0;
	float4 Color1		: COLOR1;
	float Fog           : FOG;
};


float4x4 MVP : register(c0);

float4 pos91 : register(c91);

VS_out main(in VS_in input)
{
	VS_out output;

    output.Position = mul(input.Position, MVP);
	
	output.TexCoord0.xy = input.TexCoord;
	
	output.Color0 = input.Color;
	output.Color1 = pos91.x;
	output.Fog = pos91.z;

	return output;
}
