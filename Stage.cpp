#include "Stage.h"
#include "Engine/Model.h"
#include "TestScene.h"
#include "Engine/Audio.h"
#include "Engine/CsvReader.h"
#include "Coin.h"


//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hStageModel_{ -1,-1}, table_(nullptr)
{

	CsvReader csv;
	csv.Load("map.csv");

	int width_ = csv.GetWidth();
	int height_ = csv.GetHeight();

	//table_ = new int* [csv.GetWidth()];
	table_ = new int* [width_];

	for (int x = 0; x < width_; x++)
	{
		table_[x] = new int[height_];
		for (int z = 0; z < height_; z++)
		{
			table_[x][z] = csv.GetValue(x, z); // マップデータを取得し、table_ に格納
	

		}
	}
}

//初期化
void Stage::Initialize()
{
	

	//サウンドデータのロード
	hSound_ = Audio::Load("Jazz 1.wav");
	assert(hSound_ >= 0);
	
	//モデルファイル格納してる配列
	const char* fileName[] = { "floar.fbx","floarbox.fbx"};

	//モデルデータのロード
	for (int i = 0; i < TYPE_MAX; i++)
	{
		hStageModel_[i] = Model::Load(fileName[i]);
		assert(hStageModel_[i] >= 0);
	}
	// TYPE_FCOINの場合、"floar.fbx" もロード
	//if (hModel_[TYPE_FCOIN] == true)
	//{   
	//	Model::Load(fileName[0]);
	//	/*これだとTYPE_FCOINの場合にfloar.fbxしかロードしない可能性がある*/
	//}

}

//更新
void Stage::Update()
{
	//CoinTrans.rotate_.y += 5.0f;
}

//描画
void Stage::Draw()
{
	//Coinがなぜか描画されてしまう原因
	/*現在(5/13)Coinの描画はバグっていないはず
	　Coin描画をコメントアウトしている
	  csv番号[2]の箇所は何も描画されていない
	  if文で書くか
	  　if
	  最終的に床とコインが一緒に描画されるようにする
	  目的：Coinの独立性*/

	Transform blockTrans;

	for (int x = 0; x < STAGEWIDTH ; x++)
	{
	    for (int z = 0; z <  STAGEHEIGHT; z++)
	    {
			blockTrans.position_.x = x+1;
			blockTrans.position_.z = z;

			int type = table_[x][z];
			Model::SetTransform(hStageModel_[type], blockTrans);
			Model::Draw(hStageModel_[type]);
			
		}
	}


	//for (int x = 0; x < 36; x++)
	//{
	//	for (int z = 0; z < 60; z++)
	//	{
	//		//CoinTransPosition=モデル0の位置
	//		//hCoinModel_=モデル0の床モデル
	//			CoinTrans.position_.x = x ;
	//			CoinTrans.position_.z = z ;
	//			Model::SetTransform(hCoinModel_, CoinTrans);
	//			Model::Draw(hCoinModel_);

	//	  //blockTrans.position_=モデル1の位置
	//	  //hModel_[type]=モデル１の壁モデル
	//		blockTrans.position_.x = x + 1;
	//		blockTrans.position_.z = z;
	//		int type = table_[x][z];
	//		Model::SetTransform(hModel_[type], blockTrans);
	//		Model::Draw(hModel_[type]);

	//	}
	//}
	//Audio::Play(hSound_);
}


/*コイン(仮)マップ上に配置
マップの床になっている所に配置
"floar.fbx"＝0になっている場所
当たり判定を付ける
コインを取ったら音鳴らす
Y軸で常に回転させる*/

//開放
void Stage::Release()
{
	for (int x = 0; x < width_; x++)
	{
		delete[] table_[x];
	}
	delete[] table_;
}

bool Stage::IsWall(int x, int z)
{
	if (table_[x][z] == TYPE_WALL)
		return true;
	else
		return false;
}
