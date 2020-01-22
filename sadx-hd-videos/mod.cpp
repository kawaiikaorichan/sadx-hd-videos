#include <SADXModLoader.h>
#include <IniFile.hpp>

float VideoSize_X = 640.0f;
float VideoSize_Y = 480.0f;

extern "C"
{
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
	__declspec(dllexport) void __cdecl Init(const char *path, const HelperFunctions &helperFunctions)
	{
		//Load fontdata settings
		const std::string s_path(path);
		const std::string s_config_ini(helperFunctions.GetReplaceablePath("SYSTEM\\videos.ini"));
		const IniFile* const config = new IniFile(s_config_ini);
		VideoSize_X = config->getFloat("General", "VideoSizeX");
		VideoSize_Y = config->getFloat("General", "VideoSizeY");
		delete config;
		Videos[0].Height = (int16_t)VideoSize_Y;
		Videos[0].Width = (int16_t)VideoSize_X;
		WriteData((float**)0x51392C, &VideoSize_X);
		WriteData((float**)0x513950, &VideoSize_Y);
		WriteData((int16_t*)0x513918, (int16_t)VideoSize_X);
		WriteData((int16_t*)0x513921, (int16_t)VideoSize_Y);
		if (VideoSize_X > 1024)	WriteData((Sint32*)0x10F1D68, 2048); //(Sint32)Videos[0].Width);
		if (VideoSize_Y > 1024)	WriteData((Sint32*)0x10F1D6C, 2048); //(Sint32)Videos[0].Height);
		//PrintDebug("X: %f \n", VideoSize_X);
	}
}