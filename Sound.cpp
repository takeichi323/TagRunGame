#include "Sound.h"

bool Sound::InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasteringVoice)
{
//XAudio2の初期化概要
https://learn.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--initialize-xaudio2

	//エラーを返す
	HRESULT hr{};

	//COM(Component Object Mode)ライブラリを初期化
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return false;
	}

	//XAudio2エンジンの初期化
	hr = XAudio2Create(ppXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		return false;
	}

	//マスタリング音声を生成
	hr = (*ppXAudio2)->CreateMasteringVoice(ppMasteringVoice);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

bool Sound::InitializeX3DAudio(IXAudio2MasteringVoice* pMasterVoice, X3DAUDIO_HANDLE& x3DInstance)
{
	UINT32 nChannels = 0;
	pMasterVoice->GetChannelMask();

	return false;
}

void Sound::SetupEmitter(X3DAUDIO_EMITTER& emitter)
{
}

void Sound::SetupListener(X3DAUDIO_LISTENER& listener)
{
}

void Sound::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& dspSetting)
{
	//仮置き　サイズ変更の可能性あり
	FLOAT32 matrix[8] = {};
}

bool Sound::CreateAndPlaySourceVoice(IXAudio2* pXAudio2, IXAudio2SourceVoice** ppSourceVoice, WAVEFORMATEX& waveFormat, XAUDIO2_BUFFER& buffer)
{
	HRESULT hr{};

	//ソース音声を作成
	hr = pXAudio2->CreateSourceVoice(ppSourceVoice, &waveFormat);
	if (FAILED(hr)) {
		return false;
	}

	//(音声キュー?)に新しいオーディオバッファーを追加
	hr = (*ppSourceVoice)->SubmitSourceBuffer(&buffer);
	if (FAILED(hr)) {
		return false;
	}

	//オーディオ処理スレッドを開始
	hr = (*ppSourceVoice)->Start(0);
	if (FAILED(hr)) {
		return false;
	}



	return true;
}
