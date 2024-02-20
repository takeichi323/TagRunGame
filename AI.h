#pragma once
#include <iostream>
class AI{
public:
	//純粋仮想関数:それぞれのクラスで別のことする
	virtual void Update() = 0;
};

/*実装するもの{
メタAIを実装するクラス
キャラクタAIを実装するクラス
ナビゲーションを実装するクラス
}*/
