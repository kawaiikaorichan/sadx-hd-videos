#include <SADXModLoader.h>
#include <IniFile.hpp>

float VideoSize_X = 640.0f;
float VideoSize_Y = 480.0f;

extern "C"
{
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
	__declspec(dllexport) void __cdecl Init(const char *path, const HelperFunctions &helperFunctions)
	{
		const std::string s_path(path);
		const std::string s_config_ini(helperFunctions.GetReplaceablePath("SYSTEM\\videos.ini"));
		const IniFile* const config = new IniFile(s_config_ini);
		VideoSize_X = config->getFloat("General", "VideoSizeX", 640.0f);
		VideoSize_Y = config->getFloat("General", "VideoSizeY", 480.0f);
		delete config;
		for (int i = 0; i < 9; i++)
		{
			Videos[i].Height = (int16_t)VideoSize_Y;
			Videos[i].Width = (int16_t)VideoSize_X;
		}
		WriteData((float**)0x51392C, &VideoSize_X);
		WriteData((float**)0x513950, &VideoSize_Y);
		WriteData((int16_t*)0x513918, (int16_t)VideoSize_X);
		WriteData((int16_t*)0x513921, (int16_t)VideoSize_Y);
		if (VideoSize_X > 1024)	WriteData((Sint32*)0x10F1D68, 2048);
		if (VideoSize_Y > 1024)	WriteData((Sint32*)0x10F1D6C, 2048);
	}
}