#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

/*・制限時間（タイマー）をつける
　・ハート形のライフ追加
  */



//◆◆◆を管理するクラス
class Player : public GameObject
{   
    //Player移動速度
    const float PLAYERMOVE = 0.05f;
    const float DASHPLAYERMOVE = 2.00f;

    int hModel_;    //モデル番号
    int hSound_;    //サウンド番号

    XMFLOAT3  prevPosition_;   //prev(previous)前
    Stage* pStage_;//モデル番号

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();
    //初期化
    void Initialize() override;
    //更新
    void Update() override;
    //描画
    void Draw() override;
    //開放
    void Release() override;
    //プレイヤーのカメラ位置
    void CameraPosition();
//プレイヤーの移動関数
    void PlayerMove();


    
    
};
