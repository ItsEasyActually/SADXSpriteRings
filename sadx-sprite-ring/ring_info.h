#pragma once

class sprite_info
{
public:
	int tex_total;
	int frame;
	float scale;
	NJS_ARGB color;

	std::vector<NJS_TEXNAME> texnames;
	std::vector<NJS_TEXANIM> animation;

	NJS_TEXLIST texlist;
	NJS_SPRITE sprite;

	void LoadInfo(std::shared_ptr<IniFile> file, std::string header, std::string texbasename)
	{
		Sint16 sprite_size = file->getInt(header, "Size", 16);
		Sint16 spite_center = (sprite_size / 2);

		tex_total = file->getInt(header, "TextureCount", 4);
		frame = file->getInt(header, "FrameIncrement", 6);
		scale = file->getFloat(header, "SpriteScale", 0.3f);

		for (int i = 0; i < tex_total; i++)
		{
			std::string name = texbasename + std::to_string(i);
			texnames.push_back({ (void*)name.c_str() });

			NJS_TEXANIM anim = { sprite_size, sprite_size, spite_center, spite_center, 0, 0, 255, 255, i, 0 };
			animation.push_back(anim);
		}

		texlist = { texnames.data(), texnames.size() };
		sprite = { { 0 }, scale, scale, 0, &texlist, animation.data() };
	}
};

class ring_info
{
public:
	sprite_info obj;
	sprite_info eff;

	void LoadInfoFile(std::shared_ptr<IniFile> info)
	{
		obj.LoadInfo(info, "Object", "ring");
		eff.LoadInfo(info, "Effect", "eff_ring");
	}
};

extern ring_info RingInfo;