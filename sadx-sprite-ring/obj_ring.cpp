#include "pch.h"

#define RotateZ(a) if (a) { njRotateZ(0, a); }
#define RotateX(a) if (a) { njRotateX(0, a); }

bool rendershadow = true;

DataPointer(float, late_suimen_draw_flag, 0x03ABD9CC);
FunctionHook<void, task*> hRingDisp((intptr_t)Ring_Display);
FunctionHook<void, taskwk*, float> hDispRingShadow(0x0049ED70);
FunctionHook<void, task*> hRingDispBuilding(0x00614D10);
FunctionHook<void, task*> hTpRingDisp(0x0061F290);
FunctionHook<void, task*, float> hRingDrawShadow(0x0044F960);
FunctionHook<void, NJS_MODEL_SADX*, float> hDrawRingShadow(0x00407B00);

void DrawSpriteRingShadow(taskwk* twp, float height)
{
	if (!rendershadow)
		return;

	float xscale = RingInfo.obj.shadow_scale / (fabs(twp->pos.y - height) * 0.05f + 1.0f);
	SetRegularTexture();
	njPushMatrix(0);
	njTranslate(0, twp->pos.x, (height + 0.2f), twp->pos.z);
	RotateZ(twp->ang.z);
	RotateX(twp->ang.x);
	njScale(0, xscale, xscale, xscale);
	hDrawRingShadow.Original((NJS_MODEL_SADX*)ShadowBlob_Model.model, xscale);
	njPopMatrix(1u);
}

void SpriteRingDisp(task* tp)
{
	taskwk* twp = tp->twp;

	if (!loop_count && IsVisible(&twp->pos, 40.0))
	{
		DrawSpriteRingShadow(twp, (twp->scl.y + 0.4f));
		int frame = ((FrameCounterUnpaused / RingInfo.obj.frame) % RingInfo.obj.tex_total);
		njSetTexture(&RingInfo.obj.texlist);
		njPushMatrix(0);
		njTranslate(0, twp->pos.x, twp->pos.y, twp->pos.z);
		late_SetFunc(DrawSpritePoint, (void*)frame, -100000.0f, LATE_EASY);
		njPopMatrix(1u);
	}
}

void SpriteDroppedRingDisp(task* tp, float height)
{
	taskwk* twp = tp->twp;

	if (!loop_count && IsVisible(&twp->pos, 40.0))
	{
		DrawSpriteRingShadow(twp, height);
		int frame = ((FrameCounterUnpaused / RingInfo.obj.frame) % RingInfo.obj.tex_total);
		njSetTexture(&RingInfo.obj.texlist);
		njPushMatrix(0);
		njTranslate(0, twp->pos.x, twp->pos.y + 3.44f, twp->pos.z);
		late_SetFunc(DrawSpritePoint, (void*)frame, -100000.0f, LATE_EASY);
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