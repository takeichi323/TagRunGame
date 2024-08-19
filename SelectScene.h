#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class SelectScene : public GameObject
{
    int hTitlelog_;//画像番号
    Transform transformTitlelog_;

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

