#pragma once
#include<Windows.h>
#include<X3DAudio.h>
#include<xaudio2.h>


class Sound
{

	bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasteringVoice);

	//X3DAudioの初期化
	bool Initialize3DAudio(IXAudio2MasteringVoice* pMasteringVoice, X3DAUDIO_HANDLE& x3DInstance);

	//エミッター設定
	void SetupEmitter(X3DAUDIO_EMITTER& emitter);

	//リスナーの設定
	void SetupListener(X3DAUDIO_LISTENER& listener);

};

