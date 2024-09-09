#pragma once
#include "Engine/GameObject.h"


class ResultScene : public GameObject
{
private:
	const float RESULT_POS_X = -0.4f; //リザルト画像Xポジション
	const float RESULT_POS_Y = -0.5f; //リザルト画像Yポジション
	const float TITLE_POS_X = -0.8f; //タイトル画像Xポジション
	const float TITLE_POS_Y = -0.5f; //タイトル画像Yポジション
	const float IMAGE_SCALE = 1.2f; //画像拡大量
	const float DEFAULT_SCALE = 1.0f;//画像拡大初期値
	int hResult_;
	int hBackTitle_;
	Transform transformResultlog_;
	Transform transformTitelog_;
	int selectedMode_;//0:ゲームシーン、1:タイトルシーン
	//拡大する値の初期値
	float scaleNormal_ = 1.0f;
	float scaleTitle_ = 1.0f;
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
