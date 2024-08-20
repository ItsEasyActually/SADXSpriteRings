#include "pch.h"

DataPointer(float, late_suimen_draw_flag, 0x03ABD9CC);
FunctionHook<void, task*> hRingDisp((intptr_t)Ring_Display);
FunctionHook<void, taskwk*, float> hDispRingShadow(0x0049ED70);
FunctionHook<void, task*> hRingDispBuilding(0x00614D10);
FunctionHook<void, task*> hTpRingDisp(0x0061F290);
FunctionHook<void, task*, float> hRingDrawShadow(0x0044F960);

int ringframe = 0;

void DrawSprite3DPixel(NJS_SPRITE* sp, int frame, NJD_SPRITE attr, LATE zflg)
{
	StartSpriteRender();
	PrintDebug(std::to_string(Sprite3DDepth_Current).c_str());
	late_DrawSprite3D(sp, frame, attr, zflg);
	EndSpriteRender();
}

void SpriteRingDisp(task* tp)
{
	taskwk* twp = tp->twp;

	if (!loop_count && IsVisible(&twp->pos, 40.0))
	{
		int ring = ((FrameCounterUnpaused / RingInfo.obj.frame) % RingInfo.obj.tex_total);
		njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
		njSetTexture(&RingInfo.obj.texlist);
		njPushMatrix(0);
		njTranslate(0, twp->pos.x, twp->pos.y, twp->pos.z);
		late_SetFunc(DrawSpritePoint, (void*)ring, -100000.0f, LATE_EASY);
		njPopMatrix(1u);
	}
}

void SpriteDroppedRingDisp(task* tp, float height)
{
	taskwk* twp = tp->twp;

	if (!loop_count && IsVisible(&twp->pos, 40.0))
	{
		int ring = ((FrameCounterUnpaused / RingInfo.obj.frame) % RingInfo.obj.tex_total);
		njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
		njSetTexture(&RingInfo.obj.texlist);
		njPushMatrix(0);
		njTranslate(0, twp->pos.x, twp->pos.y + (height + 0.4f), twp->pos.z);
		late_SetFunc(DrawSpritePoint, (void*)ringframe, -100000.0f, LATE_EASY);
		njPopMatrix(1u);
	}
}

void InitSpriteRingHook()
{
	hRingDisp.Hook(SpriteRingDisp);
	hRingDispBuilding.Hook(SpriteRingDisp);	
	hTpRingDisp.Hook(SpriteRingDisp);
	hRingDrawShadow.Hook(SpriteDroppedRingDisp);
}