#include "LifeGauge.h"
#include "Engine/Image.h"

//コンストラクタ
LifeGauge::LifeGauge(GameObject* parent)
    :GameObject(parent, "LifeGauge"), hPict_(-1)
{
}

//デストラクタ
LifeGauge::~LifeGauge()
{
}

//初期化
void LifeGauge::Initialize()
{
    //画像データのロード
    hPict_ = Image::Load("Frame.png");
    assert(hPict_ >= 0);
}

//更新
void LifeGauge::Update()
{
}

//描画
void LifeGauge::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//開放
void LifeGauge::Release()
{
}
