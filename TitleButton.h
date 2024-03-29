#pragma once
#include "Engine/GameObject.h"
enum NEXTSCENE {
	NONE = -1,
	TEST,
	MAX
};

class TitleButton : public GameObject {
public:
	TitleButton(GameObject* parent);
	~TitleButton();


	void Initialize() override;
	void Update() override;
	void Draw() override;

	bool Finished(); // Buttonが終わったらtrue

	//各種セット関数
	void SetImage(std::string normal);
	void SetImage(std::string normal, std::string pushed);
	void SetPosition(int x, int y);
	void SetAlphaNormal(float alpha);//通常時表示する画像　
	void SetAlphaPush(float alpha);//押されている最中に表示する画像
	void SetNextScene(NEXTSCENE next);
	void SetIsFlash(bool flash);
	int GetImageHandle() const;

	//pushedを変える
	void Push(bool pushed);

	//マウスが画像の範囲内か
	bool MouseInArea(XMFLOAT3 mousePos);


private:

	void ChangeAlpha();
	void ChangeScene();

	//画像番号
	int hImage_;

	//一応2つ目の画像番号
	int hPush_;

	//今回は画像の上にマウスがあるか
	bool pushed_;

	//中心とサイズ
	XMFLOAT3 center_;
	XMFLOAT3 size_;
	XMFLOAT3 size_2;

	//画像の点滅に関する変数
	int alpha_;//黒いStartの透明度
	int changeLimit_;
	int tmpLimit_;
	bool alphaFlag_;
	bool startFlag_;//クリックされたかのフラグ

	bool isFlash_;//待機状態で点滅させるかどうか。trueなら点滅

	NEXTSCENE nextScene_;
};

