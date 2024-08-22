#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"


//namespace {
//	float startX;//移動開始X座標
//	float endX;//移動終了X座標
//	float totalTime;//移動時間
//	float currentTime;//現在の時間
//	int seq_line;//今実行している行
//	float seq_time;//シーケンスを実行している時間
//	enum ACT {//やることをコマンド化
//		A_SLIDEIN = 1,
//		A_WAIT,
//		A_SLIDEOUT,
//		A_END
//	};
//	struct  Sequence {
//		float time;//時間
//		ACT action;//やること
//		float param;//必要な値
//	};
//	//流れを書いていく
//	Sequence tbl[] = {
//		{0.0f,A_SLIDEIN,-5.0f},//スライドイン
//		{3.0f,A_WAIT,0.0f},//１秒待ってから
//		{4.0f,A_SLIDEOUT,5.0f},//スライドアウト
//		{5.0f,A_END,0.0f}//ここで消える
//	};
//	ACT currentAction;
//	bool canMove;
//};

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}
//初期化
void ResultScene::Initialize()
{
	hResult_= Image::Load("TagRunGame_v2.png");
	assert(hResult_ >= 0);
	// 画像の位置を変更する
    transformResultlog_.position_.x = -0.4f;
    transformResultlog_.position_.y = -0.5f;

	hBackTitle_ = Image::Load("EnterPUSH logo.png");
	assert(hBackTitle_ >= 0);
    transformTitelog_.position_.x = 0.8f;
    transformTitelog_.position_.y = -0.5f;
}

//更新
void ResultScene::Update()
{
    // 入力処理
    if (Input::IsKey(DIK_LEFT)) {
        if (selectedMode_ != 0) {
            selectedMode_ = 0; // ふつうを選択
        }
    }
    
    if (Input::IsKey(DIK_RIGHT)) {
        if (selectedMode_ != 1) {
            selectedMode_ = 1; // むずかしいを選択
        }
    }

    // スケール調整
    if (selectedMode_ == 0) {
        scaleNormal = 1.2f; // ふつうの画像を拡大
        scaleHard = 1.0f;   // むずかしいの画像はそのまま
    }
    else {
        scaleNormal = 1.0f; // ふつうの画像はそのまま
        scaleHard = 1.2f;   // むずかしいの画像を拡大
    }


    // 決定処理
    if (Input::IsKey(DIK_BACK)) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        if (selectedMode_ == 0) {
            pSceneManager->ChangeScene(SCENE_ID_TEST); // ふつうのゲームモードへ(ゲームシーン)
        }
        else {
            pSceneManager->ChangeScene(SCENE_ID_TITLE); // むずかしいゲームモードへ（タイトルシーン）
        }
    }

		
}
//描画
void ResultScene::Draw()
{
    transformResultlog_.scale_ = XMFLOAT3(scaleNormal, scaleNormal, scaleNormal);
	Image::SetTransform(hResult_, transformResultlog_);
	Image::Draw(hResult_);

    // むずかしいの画像の描画
    transformTitelog_.scale_ = XMFLOAT3(scaleHard, scaleHard, scaleHard);
	Image::SetTransform(hBackTitle_, transformTitelog_);
	Image::Draw(hBackTitle_);
}
//開放
void ResultScene::Release()
{
}


