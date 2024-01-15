#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{   
private:
    //Player移動速度
    const float PLAYERMOVE = 0.1;
    //1フレームの移動ベクトル
    const XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//奥に(Z)+0.1

    Stage* pStage_;//モデル番号

    //1つ前のポジション
    XMFLOAT3  prevPosition_;  

    int hModel_;    //モデル番号
    int hSound_;    //サウンド番号
    //速度を一定にするやつ
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);
    //マウス操作がされたかどうか
    bool isMouseControl_;

    //マウス操作の処理
    void MouseControl();
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
    
    

   
    
    //壁との当たり判定
    bool WallHitTest();
};
