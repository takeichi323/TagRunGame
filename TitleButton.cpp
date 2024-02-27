#include "TitleButton.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

namespace {
	float startX; // 移動開始X座標
	float endX;   // 移動終了X座標
	float totalTime; // 移動時間（秒）
	float currentTime; // 現在の時間

	int seq_line; // 今実行している行
	float seq_time; // シーケンスを実行している時間
	enum ACT { // やることをコマンド化
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct Sequence {
		float time; // 時間
		ACT action; // やること
		float param; // 必要な値
	};
	Sequence tbl[] = {

		{ 0.0f, A_SLIDEIN, 5.0f }, // まずはスライドイン
		{ 3.0f, A_WAIT, 0.0f/*意味なし*/}, // 1秒待ってから
		{ 4.0f, A_SLIDEOUT, -5.0f }, // スライドアウト
		{ 5.0f, A_END, 0.0f} // ここで消える
	};
	ACT currentAction; // 今実行しているアクション
	bool canMove; // 移動できる
};

TitleButton :: TitleButton(GameObject* parent)
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
	alpha_ = 255;
	changeLimit_ = 0;
	tmpLimit_ = 0;
	alphaFlag_ = false;
	startFlag_ = false;
	nextScene_ = NONE;
	isFlash_ = false;
}

TitleButton::~TitleButton()
{
}

void TitleButton::Initialize()
{
	pushed_ = false;
	hImage_ = -1;
	hPush_ = -1;
	transform_.position_.x = 0.0f;
	transform_.position_.y = 0.0f;

}

void TitleButton::Update()
{

	//点滅を管理
	//isFlashがtrueなら待機状態で点滅するように
	if (isFlash_) {
		if (!startFlag_) {//クリックされたらelseになる
			ChangeAlpha();
		}
		else {
			ChangeScene();
		}
	}


	if (pushed_) {

		if (!startFlag_)
			alpha_ = 255;

		if (Input::IsMouseButtonDown(0)) {
			startFlag_ = true;
			alphaFlag_ = false;
			isFlash_ = true;
		}
	}

	Image::SetAlpha(hImage_, alpha_);
}

void TitleButton::Draw()
{

	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);

}

bool TitleButton::Finished()
{
	return canMove;
}

void TitleButton::SetImage(std::string normal)
{
	hImage_ = Image::Load((normal + ".png").c_str());
	size_ = Image::GetSize(hImage_);
}

void TitleButton::SetImage(std::string normal, std::string pushed)
{
	hImage_ = Image::Load((normal + ".png").c_str());
	hPush_ = Image::Load((pushed + ".png").c_str());
	size_ = Image::GetSize(hImage_);
}

void TitleButton::SetPosition(int x, int y)
{
	transform_.position_.x = (float)(x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = -(float)(y - Direct3D::screenHeight_ / 2) / (Direct3D::screenHeight_ / 2);
	center_ = XMFLOAT3(x, y, 0);
}

void TitleButton::Push(bool pushed)
{
	this->pushed_ = pushed;
}

bool TitleButton::MouseInArea(XMFLOAT3 mousePos)
{
	if (abs(mousePos.x - center_.x) > size_.x / 2)
		return false;
	if (abs(mousePos.y - center_.y) > size_.y / 2)
		return false;
	return true;
}

void TitleButton::SetAlphaNormal(float alpha)
{
	Image::SetAlpha(hImage_, alpha);
}

void TitleButton::SetAlphaPush(float alpha)
{
	Image::SetAlpha(hPush_, alpha);
}

void TitleButton::SetNextScene(NEXTSCENE next)
{
	nextScene_ = next;
}

void TitleButton::SetIsFlash(bool flash)
{
	isFlash_ = flash;
}

int TitleButton::GetImageHandle() const
{
	return hImage_;
}

void TitleButton::ChangeAlpha()
{
	if (!alphaFlag_) {
		alpha_ += 3;
	}
	else {
		alpha_ -= 3;
	}

	if (alpha_ >= 255)
		alphaFlag_ = true;

	if (alpha_ <= 0)
		alphaFlag_ = false;
}

void TitleButton::ChangeScene()
{
	changeLimit_++;

	if (changeLimit_ % 30 == 1) {
		alphaFlag_ = false;
	}

	if (tmpLimit_ > 15)
		alphaFlag_ = true;

	if (alphaFlag_) {
		alpha_ = 255;
		tmpLimit_ = 0;
	}
	else {
		alpha_ = 0;
		tmpLimit_++;
	}

	if (changeLimit_ > 60) {
		switch (nextScene_)
		{
		case NONE:
			break;
		case TEST: {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TEST);
		}
				   break;
		default:
			break;
		}
	}

}