#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"


namespace {
	float startX;//移動開始X座標
	float endX;//移動終了X座標
	float totalTime;//移動時間
	float currentTime;//現在の時間
	int seq_line;//今実行している行
	float seq_time;//シーケンスを実行している時間
	enum ACT {//やることをコマンド化
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct  Sequence {
		float time;//時間
		ACT action;//やること
		float param;//必要な値
	};
	//流れを書いていく
	Sequence tbl[] = {
		{0.0f,A_SLIDEIN,-5.0f},//スライドイン
		{3.0f,A_WAIT,0.0f},//１秒待ってから
		{4.0f,A_SLIDEOUT,5.0f},//スライドアウト
		{5.0f,A_END,0.0f}//ここで消える
	};
	ACT currentAction;
	bool canMove;
};

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
}
//初期化
void ResultScene::Initialize()
{
	hResult_= Image::Load("Result.png");
	assert(hResult_ >= 0);
	hBackTitle_ = Image::Load("EnterPUSH logo.png");
	assert(hBackTitle_ >= 0);
	transformResultlog_.position_.x = 0.0f;
	transformResultlog_.position_.y = 0.0f;

	startX = 5.0f;
	endX = 0;
	totalTime = 8.0f;
	currentTime = 0.0f;
	transform_.position_.x = startX;  // 初期X座標を設定
}
float easeInCubic(float x) {
	return x * x * x;
}
//更新
void ResultScene::Update()
{
	seq_time += 1.0f / 60.0f;//時間を進める
	if (seq_time >= tbl[seq_line + 1].time) {//次の行を実行する
		seq_line++;
		switch (tbl[seq_line].action) {
		case A_END:
			KillMe();
			break;
		case A_SLIDEIN:
			startX = tbl[seq_line].param;
			endX = 0;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;

			break;
		case A_WAIT:
			startX = transform_.position_.x;
			endX = transform_.position_.x;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_SLIDEOUT:

			startX = transform_.position_.x;
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			

		}
		//その行の実行をする

	}
	currentTime += 1.0f / 60.0f;//１フレーム分の時間を進ませる
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//ここを0.0～1.0の範囲にする
	float val = easeInCubic(t);
	transform_.position_.x = val * (endX - startX) + startX;

	
		// 透明度の変化を制御するフラグ
		static bool increasing = true;
		// 透明度の増減速度
		static int transparencyStep = 5;
		// 最大透明度
		static int transparencyMax = 255;
		// 現在の透明度
		static int currentTransparency = 0;
		// 透明度の増減処理
		if (increasing) {
			currentTransparency += transparencyStep;
			if (currentTransparency >= transparencyMax) {
				increasing = false;
			}
		}
		else {
			currentTransparency -= transparencyStep;
			if (currentTransparency <= 0) {
				increasing = true;
			}
		}

		// 画像の透明度を設定
		Image::SetAlpha(hBackTitle_, currentTransparency);
		if (Input::IsKey(DIK_ESCAPE)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
}
//描画
void ResultScene::Draw()
{
	
	Image::SetTransform(hResult_, transform_);
	Image::Draw(hResult_);

	Image::SetTransform(hBackTitle_, transformResultlog_);
	Image::Draw(hBackTitle_);
}
//開放
void ResultScene::Release()
{
}

bool ResultScene::Finished()
{

	return seq_line >= sizeof(tbl) / sizeof(tbl[0]) - 1;
	return canMove;
	if (currentTime >= totalTime)
		return true;
	return false;
}
