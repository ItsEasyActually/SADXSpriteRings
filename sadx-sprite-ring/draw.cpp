#include "pch.h"

// Special thanks to Kell (kellsnc) for an assist on setting up the two DrawSpritePoint functions/using late_SetFunc.

#define SetFilter(filter) (DWORD*)&filter

enum tssfilter
{
	Mag = 0,
	Min = 1,
	Mip = 2,
};

D3DTEXTUREFILTERTYPE currentFilter[3];
D3DTEXTUREFILTERTYPE userFilter;

void SetUserFilterMethod(TexFilter mode)
{
	switch (mode)
	{
	default:
	case TexFilter::Point:
		userFilter = D3DTEXF_POINT;
		break;
	case TexFilter::Linear:
		userFilter = D3DTEXF_LINEAR;
		break;
	}
}

void BackupTextureStage()
{
	// We store these to restore them later.
	_st_d3d_device_->GetTextureStageState(0, D3DTSS_MAGFILTER, SetFilter(currentFilter[0]));
	_st_d3d_device_->GetTextureStageState(0, D3DTSS_MINFILTER, SetFilter(currentFilter[1]));
	_st_d3d_device_->GetTextureStageState(0, D3DTSS_MIPFILTER, SetFilter(currentFilter[2]));
}

void StartSpriteRender()
{
	BackupTextureStage();

	// Set the current Texture Stage to render as the user supplied method.
	_st_d3d_device_->SetTextureStageState(0, D3DTSS_MAGFILTER, userFilter);
	_st_d3d_device_->SetTextureStageState(0, D3DTSS_MINFILTER, userFilter);
	_st_d3d_device_->SetTextureStageState(0, D3DTSS_MIPFILTER, userFilter);
}

void EndSpriteRender()
{
	// Restore the backuped Texture Stage Filter method.
	_st_d3d_device_->SetTextureStageState(0, D3DTSS_MAGFILTER, currentFilter[0]);
	_st_d3d_device_->SetTextureStageState(0, D3DTSS_MINFILTER, currentFilter[1]);
	_st_d3d_device_->SetTextureStageState(0, D3DTSS_MIPFILTER, currentFilter[2]);
}

void DrawSpritePoint(void* data)
{
	StartSpriteRender();

	int frame = *(int*)&data;
	njDrawSprite3D(&RingInfo.obj.sprite, frame, NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE);

	EndSpriteRender();
}

void DrawEffectSpritePoint(void* data)
{
	StartSpriteRender();

	int frame = *(int*)&data;
	njDrawSprite3D(&RingInfo.eff.sprite, frame, NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE);

	EndSpriteRender();
}