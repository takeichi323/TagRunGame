#include "Stage.h"
#include "Engine/Model.h"
#include "TestScene.h"
#include "Engine/CsvReader.h"

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
			//���Ƃ��Ȃ�I�I�t�@�C�g����I

		}
	}
}

//������
void Stage::Initialize()
{
	const char* fileName[] = { "floar.fbx", "floarbox.fbx"};

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
}

//�`��
void Stage::Draw()
{

	Transform blockTrans;

	for (int x = 0; x < 34; x++)
	{
		for (int z = 0; z <58; z++)
		{
			blockTrans.position_.x = x;
			blockTrans.position_.z = z;

			int type = table_[x][z];
			Model::SetTransform(hModel_[type], blockTrans);
			Model::Draw(hModel_[type]);
		}
	}
}

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
