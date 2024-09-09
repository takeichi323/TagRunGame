#pragma once
#include "Engine/GameObject.h"


//Titleシーンを管理するクラス
class TitleScene : public GameObject
{
private:
	const float PUSHLOGPOS_X = 0.0f;
	const float PUSHLOGPOS_Y = -0.6f;
	const float TITLELOGPOS_X = 0.0f;
	const float TITLELOGPOS_Y = 0.0f;
	const float BLINKING_SPEED = 10.0f;//点滅速度
	const float TRANSPARENCY_UPDATE = 5.0f;//透明度更新

	int hPict_;    //画像番号
	int hTitlelog_;//画像番号
	int hBlack_;  // 黒い画像用
	Transform transformTitlelog_;
	Transform transformpushlog_;
	Transform transformBlack_;

    // 現在の透明度
	int currentTransparency_ = 0;
	// 透明度の変化を制御するフラグ
	bool increasing_ = true;
	//点滅と暗転の開始を示すフラグ
	bool transitionmove_;
	// 画面暗転時の透明度
    int transitionTransparency_;
	// 最大透明度
    int transparencyMax_ = 255;
	// 透明度の増減速度
	int transparencyStep_ = 5;
	// 暗転速度を制御するための変数
	float fadeSpeed_ = 150.0f;
	

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
	
};


