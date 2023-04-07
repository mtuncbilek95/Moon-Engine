# Moon-Engine

```hlsl
float2 CalculateUV(float2 uv, float2 dimensions, int index)
{
	float2 spriteSize = { 1.0f / dimensions.x, 1.0f / dimensions.y };

	int spriteX = index % int(dimensions.x);
	int spriteY = index / int(dimensions.x);

	float2 offset = { spriteX * spriteSize.x, spriteY * spriteSize.y };

	float2 UV = { (uv.x * spriteSize.x) + offset.x, (uv.y * spriteSize.y) + offset.y };

	return UV;
}
```
