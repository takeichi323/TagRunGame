#include "AI.h"
//ナビゲーションAIクラス
class NavigationAI :public AI {
public:
    //更新処理
    virtual void Update()override;
    /*ナビゲーションAIやること
     経路探索をする場所＆経路の追従
     障害物の情報を取得

    */
};
