#pragma once
#include "Engine/GameObject.h"


class ResultScene : public GameObject
{
private:
	int hResult_;
	int hBackTitle_;
	Transform transformResultlog_;
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
	bool Finished();
};
