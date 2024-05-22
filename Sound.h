#pragma once
#include<Windows.h>
#include<X3DAudio.h>
#include<xaudio2.h>

//ƒ‰ƒCƒuƒ‰ƒŠ“Ç‚İ‚İ
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")

class Sound
{

  //XAudio2‚Ì‰Šú‰»
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudio‚Ì‰Šú‰»
   bool InitializeX3DAudio(IXAudio2MasteringVoice* pMasterVoice, X3DAUDIO_HANDLE& x3DInstance);



};

