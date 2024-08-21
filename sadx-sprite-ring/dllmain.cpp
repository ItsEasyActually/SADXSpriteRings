#include "pch.h"

PVMEntry RingSpritePVM = { "OBJ_RING", nullptr };
PVMEntry RingEffectPVM = { "EFF_RING", nullptr };

ring_info RingInfo;

extern "C"
{
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		std::string spritepath;
		spritepath.append("system\\sprite.ini");
		std::shared_ptr<IniFile> info = std::make_shared<IniFile>(helperFunctions.GetReplaceablePath(spritepath.c_str()));

		std::string modpath = path;
		modpath.append("\\config.ini");
		std::shared_ptr<IniFile> config = std::make_shared<IniFile>(modpath.c_str());
		SetUserFilterMethod(static_cast<TexFilter>(config->getInt("Sprite Options", "filter", 0)));
		rendershadow = config->getBool("Sprite Options", "rendershadow", true);

		RingInfo.LoadInfoFile(info);

		RingSpritePVM.TexList = &RingInfo.obj.texlist;
		RingEffectPVM.TexList = &RingInfo.eff.texlist;

		helperFunctions.RegisterCommonObjectPVM(RingSpritePVM);
		helperFunctions.RegisterCommonObjectPVM(RingEffectPVM);

		InitSpriteRingHook();
		InitRingCollectEffect();
	}
}