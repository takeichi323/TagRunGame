#pragma once
#include "Engine/GameObject.h"
#include "TitleButton.h"



//■■シーンを管理するクラス
class TitleScene : public GameObject
{
private:
	int hSubLogo_; //画像番号
	HANDLE hFile_;        //ファイルのハンドル
	Transform start_Transform_;//Startの位置を調整する為の変数
	TitleButton* start_;
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


