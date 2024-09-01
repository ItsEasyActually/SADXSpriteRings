#include "pch.h"

UsercallFuncVoid(hCollectRingDisp, (taskwk* twp), (twp), 0x0044F7A0, rESI);

void RingDone(taskwk* twp)
{
	if (!ChkPause())
	{
		twp->counter.f += 1.0f / RingInfo.eff.frame;
	}

	if (!loop_count)
	{
		int texcount = RingInfo.eff.tex_total;
		njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
		njSetTexture(&RingInfo.eff.texlist);

		if (twp->counter.f < texcount && twp->counter.f >= 0)
		{
			njPushMatrix(0);
			njTranslate(0, twp->pos.x, twp->pos.y, twp->pos.z);
			late_SetFunc(DrawEffectSpritePoint, (void*)(int)twp->counter.f, -100000.0f, (NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE));
			njPopMatrix(1);
		}

		if (twp->counter.f > texcount)
			twp->mode = 3;
	}
}

void InitRingCollectEffect()
{
	hCollectRingDisp.Hook(RingDone);
}