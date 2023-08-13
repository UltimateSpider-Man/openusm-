struct VS_out {
	float4 Position		: POSITION;
	float2 TexCoord0	: TEXCOORD0;
	float2 TexCoord1	: TEXCOORD1;
	float4 Color		: COLOR0;
};

sampler2D tex0 : register(s0);
sampler2D tex1 : register(s1);


float4 main(VS_out input) : COLOR
{
	//float4 color = input.Color;
	const float4 p0 = tex2D(tex0, input.TexCoord0);
	
	
	float4 color;
    color.xyz = input.Color * p0;
    color.w = p0.w;
    
    float4 p1 = tex2D(tex1, input.TexCoord1);
    
    color.xyz = color * p1.w;
    color.xyz += p1;

	return color;
}
