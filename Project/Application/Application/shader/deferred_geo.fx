/**
	@file deferred_geo.fx
	@brief ディファード　ジオメトリパス
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
//semantic
float4x4	g_mWorld				: World;
float4x4	g_mWorldView			: WorldView;
float4x4	g_mWorldViewProjection	: WorldViewProjection;
float3		g_v3CameraPosition		: CameraPosition;
float3		g_f3LightDir			: DirectionalLightDir;
float3		g_f3Ambient				: Ambient;
texture		g_DiffuseTexture		: DiffuseTexture;

texture		g_NormalMap;
float  g_Specular;       //スペキュラーの範囲
float  g_SpecularPower;  //スペキュラーの強度

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler DiffuseTextureSampler = sampler_state
{
    Texture = <g_DiffuseTexture>;    
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler NormalMapSampler = sampler_state
{
    Texture = <g_NormalMap>;    
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

//--------------------------------------------------------------------------------------
// struct
//--------------------------------------------------------------------------------------
struct INPUT
{
	float4 pos		: POSITION;
	float3 normal	: NORMAL;
	float3 tangent  : TANGENT0;
	float2 uv		: TEXCOORD0;
};
struct OUTPUT
{
	float4 pos		: POSITION;
	float4 WPos		: TEXCOORD0;
	float3 WNormal	: TEXCOORD1;
	float3 uv		: TEXCOORD2;
};
struct PS_OUTPUT
{
   float4 depth : COLOR0;
   float4 color2 : COLOR1;
};

//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main_VS( INPUT IN
                )
{
	OUTPUT OUT;

	OUT.pos = mul(IN.pos, g_mWorldViewProjection);
	OUT.WPos = OUT.pos;
	OUT.uv = IN.uv;

	float3 N = mul(IN.normal, (float3x3)g_mWorld);
	float3 T = mul(IN.tangent, (float3x3)g_mWorld);
	float3 B = cross(N, T);
	
	float4 position = mul(IN.pos, g_mWorld);
	float3 E = g_v3CameraPosition - position.xyz;
	OUT.E.x = dot(E, T);
	OUT.E.y = dot(E, B);
	OUT.E.z = dot(E, N);
	OUT.E = normalize( OUT.E );

	float3 L = -g_f3LightDir.xyz;
	OUT.L.x = dot(L, T);
	OUT.L.y = dot(L, B);
	OUT.L.z = dot(L, N);
	OUT.L = normalize( OUT.L );
	
	return OUT;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
PS_OUTPUT main_PS( OUTPUT IN )
{
	PS_OUTPUT OUT;

	float3 normal = 2.0f * tex2D( NormalMapSampler, IN.uv ).xyz - 1.0f;

	float3 H = normalize( IN.L + IN.E );
	float S = pow( max( 0.5f, dot( normal, H ) ), g_Specular ) * g_SpecularPower;

	OUT.color1 = tex2D( DiffuseTextureSampler, IN.uv );
	OUT.color1 *= max( 0.2, dot( normal, IN.L ) ) + S;

	OUT.color2 = IN.WPos.z / IN.WPos.w;

	return OUT;
}


//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------
technique render
{
    pass P0
    {
        VertexShader = compile vs_2_0 main_VS();
        PixelShader = compile ps_2_0 main_PS();
    }
}



