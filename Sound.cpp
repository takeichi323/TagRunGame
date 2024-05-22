#include "Sound.h"

bool Sound::InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice)
{
	HRESULT hr{};

	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	return false;
}

bool Sound::InitializeX3DAudio(IXAudio2MasteringVoice* pMasterVoice, X3DAUDIO_HANDLE& x3DInstance)
{
	return false;
}
