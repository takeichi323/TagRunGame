#include "LifeGauge.h"
#include "Engine/Image.h"

//コンストラクタ
LifeGauge::LifeGauge(GameObject* parent)
    :GameObject(parent, "LifeGauge"), hFrame_(-1)
{
}

//デストラクタ
LifeGauge::~LifeGauge()
{
}

//初期化
void LifeGauge::Initialize()
{
    transform_.position_.x = -0.95f;
    transform_.position_.y = 0.8f;
    //画像データのロード
    hFrame_ = Image::Load("Frame.png");
    assert(hFrame_ >= 0);
}

//更新
void LifeGauge::Update()
{
}

//描画
void LifeGauge::Draw()
{
   // Image::SetTransform(hFrame_, transform_);
    //Image::Draw(hFrame_);
}

//開放
void LifeGauge::Release()
{
}
