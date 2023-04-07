# Moon-Engine

```cpp
v2d CalculateUV(v2d uv, v2d dimensions, int index)
{
	v2d spriteSize = { 1.0f / dimensions.x, 1.0f / dimensions.y };

	int spriteX = index % int(dimensions.x);
	int spriteY = index / int(dimensions.x);

	v2d offset = { spriteX * spriteSize.x, spriteY * spriteSize.y };

	v2d UV = { (uv.x * spriteSize.x) + offset.x, (uv.y * spriteSize.y) + offset.y };

	return UV;
}
```
