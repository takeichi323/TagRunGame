#include "LifeGauge.h"
#include "Engine/Image.h"

//�R���X�g���N�^
LifeGauge::LifeGauge(GameObject* parent)
    :GameObject(parent, "LifeGauge"), hPict_(-1)
{
}

//�f�X�g���N�^
LifeGauge::~LifeGauge()
{
}

//������
void LifeGauge::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load("Frame.png");
    assert(hPict_ >= 0);
}

//�X�V
void LifeGauge::Update()
{
}

//�`��
void LifeGauge::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//�J��
void LifeGauge::Release()
{
}
