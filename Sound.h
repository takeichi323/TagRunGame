#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>

//ライブラリ読み込み
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")

class Sound
{

  //XAudio2の初期化
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudioの初期化
   bool InitializeX3DAudio(IXAudio2MasteringVoice* pMasterVoice, X3DAUDIO_HANDLE& x3DInstance);

   //エミッタの設定
   void SetupEmitter(X3DAUDIO_EMITTER& emitter);

   //リスナーの設定
   void SetupListener(X3DAUDIO_LISTENER& listener);



};

