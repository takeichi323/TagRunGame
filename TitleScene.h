#pragma once
#include "Engine/GameObject.h"


//Titleシーンを管理するクラス
class TitleScene : public GameObject
{
private:
	int hPict_;    //画像番号
	int hTitlelog_;//画像番号
	Transform transformTitlelog_;

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


