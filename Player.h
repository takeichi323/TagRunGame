#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{   
private:
    //Player移動速度
    const float PLAYERMOVE = 0.25;

    int hModel_;    //モデル番号
    int hSound_;    //サウンド番号
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
    //プレイヤー向き
    void Direction();
};
