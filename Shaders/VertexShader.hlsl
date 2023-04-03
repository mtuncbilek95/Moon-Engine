cbuffer modelMatrix : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer tilepoint : register (b1)
{
	float2 tile;
}