#pragma once
#include <x3daudio.h>

//エミッター情報の構造体
struct SoundEmitter{
	//X3DAudioのエミッター構造体
	X3DAUDIO_EMITTER emitter;

	//X3DAudioのDSP設定構造体
	X3DAUDIO_DSP_SETTINGS dspSettings;

private:
	float volume;        //音量
	float minDistance;  //最小距離
	float maxDistance;  //最大距離
	
};

//リスナー情報の構造体
struct Listener{

	//X3DAudioのリスナー構造体
	X3DAUDIO_LISTENER listener;

	//その他追加予定

};

class Sound
{
	//X3DAudioの初期化
	void  InitializeX3DAudio();

	//音源配置の計算
	void CalculateSoundPosition(Listener& listener, SoundEmitter* emitters, int numEmitters);

};

