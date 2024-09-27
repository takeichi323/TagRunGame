#pragma once
#include "Engine/GameObject.h"
#include "TrackingAI.h"
#include "Player.h"

//◆◆◆を管理するクラス
class Enemy : public GameObject
{
    //Enemyの移動速度
    const float ENEMYMOVE = 0.08f;

    int hModel_;    //モデル番号
    float colliderRadius = 0.5f;//衝突判定に使う半径
    TrackingAI* trackingAI_;
    Player* player_;  //プレイヤのポインタ
    Stage* pStage_; //ステージのポインタ
    XMFLOAT3  prevPosition_;   //prev(previous)前
    XMFLOAT3 move;  // 3Dの移動量ベクトルを定義
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

    //衝突判定
    void CollisionDetection();

    //プレイヤー方向の計算
    XMFLOAT3 CalculateDirectionToPlayer(const XMFLOAT3& playerPosition) ;

    //開放
    void Release() override;
};

