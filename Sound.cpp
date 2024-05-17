#include "Sound.h"

void Sound::InitializeX3DAudio()
{
	//X3DAudioの初期化処理を追加
}

void Sound::CalculateSoundPosition(Listener& listener, SoundEmitter* emitters, int numEmitters)
{
    //X3DAudioオブジェクトの作成
    X3DAUDIO_HANDLE x3DInstance{};
   /* X3DAUdioInitialize(D3D_AUDIO_TO_PROCESSOR, X3DAUDIO_SPEED_OF_SOUND, x3DInstance);
    //リスナー情報の設定
    X3DAudioCalculate(x3DInstance, &listener.listener, emitters[0].emitter, X3DAUDIO_CALCULATE_MATRIX);
    //各音源の配置計算
    for (int i = 0; i < numEmitters; i++) {
        X3DAudioCalculate(x3DInstance, &listener.listener, emitters[i].emitter, X3DAUDIO_CALCULATE_DSP_SETTINGS);
     }*/
}
