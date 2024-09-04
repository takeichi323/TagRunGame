#pragma once
#include "Engine/GameObject.h"
#include "TrackingAI.h"
#include "Player.h"

//◆◆◆を管理するクラス
class Enemy : public GameObject
{
    int hModel_;    //モデル番号
    TrackingAI* TrackingAI_;
    Player* Player_;  //プレイヤのポインタ
public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

