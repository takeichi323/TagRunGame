#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Enemy : public GameObject
{
    int hModel_;    //モデル番号
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

    //プレイヤーの当たり判定を敵にも追加する
    //当たり判定自体をクラス化した方がいい
};

