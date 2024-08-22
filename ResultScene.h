#pragma once
#include "Engine/GameObject.h"


class ResultScene : public GameObject
{
private:
	int hResult_;
	int hBackTitle_;
	Transform transformResultlog_;
	Transform transformTitelog_;
	int selectedMode_;//0:ふつう、1:むずかしい
	//拡大する値の初期値
	float scaleNormal = 1.0f;
	float scaleHard = 1.0f;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;

	//開放
	void Release() override;
};
