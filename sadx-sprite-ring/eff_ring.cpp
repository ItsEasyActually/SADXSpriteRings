#include "pch.h"

UsercallFuncVoid(hCollectRingDisp, (taskwk* twp), (twp), 0x0044F7A0, rESI);

void RingDone(taskwk* twp)
{
	if (!ChkPause())
	{
		twp->counter.f += 0.8f;
		twp->scl.x += 0.8f;
		twp->scl.z += 0.8f;
	}

	if (!loop_count)
	{
		int texcount = RingInfo.eff.tex_total;
		njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
		njSetTexture(&RingInfo.eff.texlist);

		float n[3];
		n[0] = twp->counter.f;
		n[1] = twp->scl.x;
		n[2] = twp->scl.z;

		for (Uint8 i = 0; i < 3; i++)
		{
			if (n[i] < texcount && n[i] >= 0)
			{
				njPushMatrix(0);
				njTranslate(0, twp->pos.x - i + i, twp->pos.y - (n[i] * 0.05f) * 3.0f, twp->pos.z - i + i);
				late_DrawSprite3D(&RingInfo.eff.sprite, n[i], NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE, LATE_EASY);
				late_SetFunc(DrawEffectSpritePoint, (void*)(int)n[i], -100000.0f, (NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE));
				njPopMatrix(1);
			}
		}

		if (n[2] > texcount)
			twp->mode = 3;
	}
}

void InitRingCollectEffect()
{
	hCollectRingDisp.Hook(RingDone);
}