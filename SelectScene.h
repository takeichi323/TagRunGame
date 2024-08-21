#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class SelectScene : public GameObject
{
    int hPictNormal_;//画像番号
    int hPictHard_;//画像番号
    Transform transformNormal_;
    Transform transformHard_;
    int selectedMode_;//0:ふつう、1:むずかしい

    //拡大する値の初期値
    float scaleNormal = 1.0f;
    float scaleHard = 1.0f;

public:
    //コンストラクタ
    SelectScene(GameObject* parent);

    //デストラクタ
    ~SelectScene();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

