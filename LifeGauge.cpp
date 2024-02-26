#include "LifeGauge.h"
#include "Engine/Image.h"

//�R���X�g���N�^
LifeGauge::LifeGauge(GameObject* parent)
    :GameObject(parent, "LifeGauge"), hFrame_(-1)
{
}

//�f�X�g���N�^
LifeGauge::~LifeGauge()
{
}

//������
void LifeGauge::Initialize()
{
    transform_.position_.x = -0.95f;
    transform_.position_.y = 0.8f;
    //�摜�f�[�^�̃��[�h
    hFrame_ = Image::Load("Frame.png");
    assert(hFrame_ >= 0);
}

//�X�V
void LifeGauge::Update()
{
}

//�`��
void LifeGauge::Draw()
{
   // Image::SetTransform(hFrame_, transform_);
    //Image::Draw(hFrame_);
}

//�J��
void LifeGauge::Release()
{
}
