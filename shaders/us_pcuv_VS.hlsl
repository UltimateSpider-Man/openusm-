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


float4 pos0 : register(c0);
float4 pos1 : register(c1);
float4 pos2 : register(c2);
float4 pos3 : register(c3);

float4 c91 : register(c91);

VS_out main(in VS_in input)
{
	VS_out output;

    output.Position.x = dot(input.Position, pos0);
    output.Position.y = dot(input.Position, pos1);
    output.Position.z = dot(input.Position, pos2);
    output.Position.w = dot(input.Position, pos3);
    
	
	output.TexCoord0.xy = input.TexCoord;
	
	output.Color0 = input.Color;
	output.Color1 = c91.x;
	output.Fog = c91.z;

	return output;
}
