#include "Stage.h"
#include "Engine/Model.h"
#include "TestScene.h"
#include "Engine/CsvReader.h"
#include "Coin.h"


//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_{ -1,-1 }, table_(nullptr)
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
			table_[x][z] = csv.GetValue(x, z); // �}�b�v�f�[�^���擾���Atable_ �Ɋi�[
	

		}
	}
}

//������
void Stage::Initialize()
{
	
	const char* fileName[] = { "floar.fbx", "floarbox.fbx"};

	//�R�C���̃��f���f�[�^��ǂݍ���
	hCoinModel_ = Model::Load("Coin.fbx");
	assert(hCoinModel_ >= 0);

	//CSV�f�[�^��ǂݍ��݁A�R�C���̈ʒu�����
	CsvReader coinCsv;
	coinCsv.Load("coin_map.csv");

	//�R�C����z�u������W�̃��X�g
	std::vector<std::pair<int, int>>coinPosition;

	//CSV�f�[�^��ǂݍ���ŁA�R�C�����z�u����Ă�����W���擾
	for (int x = 0; x < coinCsv.GetWidth(); x++) {
		for (int z = 0; z < coinCsv.GetHeight(); z++) {
			if (coinCsv.GetValue(x, z) == 1) {
				coinPosition.push_back(std::make_pair(x, z));
			}
		}
	}
	

	////�R�C����z�u
	//for (const auto& position : coinPosition) {
	//	Coin coin;
	//	coin.CoinTrans.position_.x = position.first + 0.5f;
	//	coin.CoinTrans.position_.z = position.second + 0.5f;
	//	coins.push_back(coin); // coins �x�N�^�[�ɃR�C����ǉ�
	//}


	//���f���f�[�^�̃��[�h
	for (int i = 0; i < TYPE_MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}

	
}

//�X�V
void Stage::Update()
{
	CoinTrans.rotate_.y += 5.0f;
}

//�`��
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
				SphereCollider* collision = new SphereCollider(CoinTrans.position_, 0.2f);
			     AddCollider(collision);
			
			blockTrans.position_.x = x + 1;
			blockTrans.position_.z = z;

			int type = table_[x][z];
			Model::SetTransform(hModel_[type], blockTrans);
			Model::Draw(hModel_[type]);


		}
	}
		
}


/*�R�C��(��)�}�b�v��ɔz�u
�}�b�v�̏��ɂȂ��Ă��鏊�ɔz�u
"floar.fbx"��0�ɂȂ��Ă���ꏊ
�����蔻���t����
�R�C����������特�炷
Y���ŏ�ɉ�]������*/

//�J��
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
