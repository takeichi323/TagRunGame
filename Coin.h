#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Coin : public GameObject
{

    int hCoinModel_;       //コインモデル
   
public:
    //コンストラクタ
    Coin(GameObject* parent);
    Coin() {}

    

    //デストラクタ
    ~Coin();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;
    Transform CoinTrans;
    //std::vector<Coin> coins; // coins メンバーの定義


};

/*コインの単体化
　*/
