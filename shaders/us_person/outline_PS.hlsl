struct VS_out {
	float4 Position		: POSITION;
	float2 TexCoord0	: TEXCOORD0;
	float4 Color		: COLOR0;
};

float4 c0 : register(c0);


float4 main(VS_out input) : COLOR
{
    
    //return float4(0, 1, 0, 0.5);
	return c0;
}
