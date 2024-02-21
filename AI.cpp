#include <iostream>
#include <cmath>
#include "AI.h"
#include "Player.h"
#include "Enemy.h"

AI::AI()
{
}

//プレイヤーと敵の座標を取得する関数
void AI::GetPosition(Point& player, Point& enemy)
{
    /*プレイヤーの位置と敵の位置を引数にぶち込む
    　座標データが入った変数を参照させる*/
}

float AI::RangeCalculation(const Point& p1, const Point& p2)
{
    /*2点の位置を計算して数値をreturnで返す*/
    return 0.0f;
}

void AI::MoveTowards(Point& enemy, const Point& player, float speed)
{
    /*プレイヤーに向かって移動する
    　プレイヤーの方向への単位ベクトルを計算
     　移動量を計算し、敵を移動させる*/
}

void AI::MetaAI()
{
    /*メタAIやること
     キャラクターAIとナビゲーションAiの仲介役
     ナビゲーションAIから情報を取得
     他のAiに指示出し*/
}

void AI::CharacterAI()
{
}

void AI::NavigationAI()
{
    /*マップ情報＆主人公の位置＆自分の位置取得*/

}
