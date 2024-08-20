#pragma once

DataPointer(IDirect3DDevice8*, _st_d3d_device_, 0x03D128B0);

enum class TexFilter
{
	Point = 0,
	Linear = 1,
};

struct render_info
{
	NJS_SPRITE* sprite;
	int frame;
	NJD_SPRITE attr;
};

void StartSpriteRender();
void EndSpriteRender();
void SetUserFilterMethod(TexFilter mode);
void DrawSpritePoint(void* data);
void DrawEffectSpritePoint(void* data);