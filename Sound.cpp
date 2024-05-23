#include "Sound.h"

bool Sound::InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice)
{
	HRESULT hr{};

	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return false;
	}
	hr = XAudio2Create(ppXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		return false;
	}
	hr = (*ppXAudio2)->CreateMasteringVoice(ppMasterVoice);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

bool Sound::InitializeX3DAudio(IXAudio2MasteringVoice* pMasterVoice, X3DAUDIO_HANDLE& x3DInstance)
{
	return false;
}
