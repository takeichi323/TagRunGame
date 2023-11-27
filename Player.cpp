#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"



#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")









//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), hSound_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //�T�E���h�f�[�^�̃��[�h
    hSound_ = Audio::Load("Jazz 1.wav");
    assert(hSound_ >= 0);


    /// <summary>
    /// ///////////////////////////////////////////
    /// </summary>
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) {
        // �������Ɏ��s
        // �G���[����
    }
    IMFSourceReader* pReader = nullptr;

    hr = MFCreateSourceReaderFromURL(L"TouhokuDenshi_splash.avi", nullptr, &pReader);
    if (FAILED(hr)) {
        // Source Reader �̍쐬�Ɏ��s
        // �G���[����
    }
    IMFMediaType* pMediaType = nullptr;

    hr = MFCreateMediaType(&pMediaType);
    if (SUCCEEDED(hr)) {
        hr = pMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    }

    hr = pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, nullptr, pMediaType);
    while (true) {
        DWORD dwFlags = 0;
        LONGLONG llTimeStamp = 0;
        IMFSample* pSample = nullptr;

        hr = pReader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, nullptr, &dwFlags, &llTimeStamp, &pSample);
        if (FAILED(hr)) {
            // �T���v���̓ǂݎ��Ɏ��s�܂��͏I��
            break;
        }

        if (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM) {
            // �t�@�C���̏I�[�ɓ��B
            break;
        }

        // �e�N�X�`���Ƀt���[����`�悷�鏈��
    }
    pReader->Release();
    pMediaType->Release();
    MFShutdown();
    /////////////////////////////////////////////////////////////////

}

//�X�V
void Player::Update()
{
    //�J�����ʒu
      CameraPosition();
    
    //�X�y�[�X�L�[��������Ă�����
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += 0.25;
        Audio::Play(hSound_);
    }
    //�X�y�[�X�L�[��������Ă�����
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= 0.25;
        Audio::Stop(hSound_);
    }
}

//�`��
void Player::Draw()
{
   
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    
}

//�J��
void Player::Release()
{
}

//�J�����ʒu(��l��)
void Player::CameraPosition()
{
    //1�t���[���̈ړ��x�N�g��
    XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//����0.1��
    //�I�u�W�F�N�g�̌��ݒn���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    Camera::SetPosition(transform_.position_);
    XMFLOAT3 camTarget;
    XMStoreFloat3(&camTarget, vPos + vMove);
    Camera::SetTarget(camTarget);
}


