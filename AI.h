#pragma once
#include <iostream>

//オブジェクトの座標を表す構造体
struct Point
{
	float x;
	float y;

};

class AI{
public:


	//コンストラクタ
	AI();

	//座標取得関数
	void GetPosition(Point& player, Point& enemy);
	//２つ(player,enemy)の距離を計算する関数
	float RangeCalculation(const Point& p1, const Point& p2);

	//メタAI
	void MetaAI();
	//キャラクタAI
	void CharacterAI();
	//ナビゲーションAI
	void NavigationAI();




};

/*実装するもの{
メタAIを実装するクラス
キャラクタAIを実装するクラス
ナビゲーションを実装するクラス
}*/
