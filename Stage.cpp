#include "Stage.h"
#include "Engine/Model.h"
#include "TestScene.h"
#include "Engine/Audio.h"
#include "Engine/CsvReader.h"
#include "Coin.h"


//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_{ -1,-1,-1 }, table_(nullptr)
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
	

	hModel_[TYPE_FLOOR] = Model::Load("floar.fbx");
	assert(hModel_[TYPE_FLOOR] >= 0);

	//壁のロード
	hModel_[TYPE_WALL] = Model::Load("floarbox.fbx");
	assert(hModel_[TYPE_WALL] >= 0);

	//床ロード
	hModel_[TYPE_FCOIN] = Model::Load("Coin.fbx");
	assert(hModel_[TYPE_FCOIN] >= 0);

	// TYPE_FCOINの場合、"Coin.fbx" もロード
	if (table_ != nullptr) {
		for (int x = 0; x < width_; x++) {
			for (int z = 0; z < height_; z++) {

				if (table_[x][z] == TYPE_FCOIN) {
					hModel_[TYPE_FCOIN] = Model::Load("floar.fbx");
					assert(hModel_[TYPE_FCOIN] >= 0);
					
				}
			}
		}
	}	
}

//更新
void Stage::Update()
{
	//CoinTrans.rotate_.y += 5.0f;
}

//描画
void Stage::Draw()
{

	Transform blockTrans;

	for (int x = 0; x < 36; x++)
	{
		for (int z = 0; z < 60; z++)
		{
			
				CoinTrans.position_.x = x + 0.5f;
				CoinTrans.position_.z = z + 0.5f;
				Model::SetTransform(hCoinModel_, CoinTrans);
				Model::Draw(hCoinModel_);
			/*	SphereCollider* collision = new SphereCollider(CoinTrans.position_, 0.2f);
			     AddCollider(collision);*/
			
			blockTrans.position_.x = x + 1;
			blockTrans.position_.z = z;

			int type = table_[x][z];
			Model::SetTransform(hModel_[type], blockTrans);
			Model::Draw(hModel_[type]);

		}
	}
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
