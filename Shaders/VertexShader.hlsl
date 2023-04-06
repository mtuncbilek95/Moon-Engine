cbuffer tilepoint : register (b0)
{
	float2 tile;
    matrix world;
    matrix view;
    matrix projection;
}
struct pOut
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD0;
};

struct vOut
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
};

pOut main(vOut input)
{
    pOut vso;
    vso.pos = float4(input.pos, 1.0f);
    vso.uv = input.uv;
    
    vso.uv.x += tile.x;
    
    if (tile.y % vso.uv.y >= 1)
        vso.uv.y += tile.y;

    return vso;
}