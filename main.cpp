#include "pch.h"
#include "cwe_api.h"
#include "ModelInfo.h"

extern "C"
{
	//registering data functions. - Needs to exist.
	void (*RegisterDataFunc)(void* ptr);

	//Define Models
	ModelInfo* MDLExampleChao;

	//Define a pointer function for pEvolveFunc
	static bool CosmoEvolve(ObjectMaster* tp)
	{
		if (tp->Data1.Chao->ChaoDataBase_ptr->Alignment > 0.75 && tp->Data1.Chao->ChaoDataBase_ptr->SA2BCharacterBonds[2].a > 75)
		{
			PrintDebug("Chao evolving");
			return true;
		}
		else
			return false;
	}

	//main CWE Load function -- Important stuff like adding your CWE mod goes here
	void CWELoad(CWE_REGAPI* cwe_api, ObjectMaster* tp)
	{

		//Define Character Chao data:
		CWE_API_CHAO_DATA CharChao_pData =
		{
			MDLExampleChao->getmodel(),	//pObject
			{0},				//pSecondEvoList[5]

			"CosmoChao",			//TextureName
			7,				//TextureCount
			0xFF8CB2B3,			//IconColor - hex, 4 bytes (0xAARRGGBB)
			ICON_TYPE_HALO,			//IconType
			NULL,				//pIconData

			CosmoEvolve,			//pEvolveFunc 

			0,				//Flags
			"Cosmo",			//Name
			"cwe_cosmo",			//id
		};
		
		//add the Chao Type
		cwe_api->AddChaoType(&CharChao_pData);
	}

	//initialization function - MUST exist in order to have CWE and SA2 see your mod
	__declspec(dllexport) void Init(const char* path)
	{
		HMODULE h = GetModuleHandle(L"CWE");

		std::string pathStr = std::string(path) + "\\";

		MDLExampleChao = new ModelInfo(pathStr + "MDLExampleChao.sa2mdl");

		RegisterDataFunc = (void (*)(void* ptr))GetProcAddress(h, "RegisterDataFunc");
		RegisterDataFunc(CWELoad);
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}
