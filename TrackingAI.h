#include "Engine/GameObject.h"
#include "Vector3.h"

class TrackingAI{
public:
	TrackingAI(GameObject* parent);
	~TrackingAI();

	void SetDestination(const XMFLOAT3& destination);
	void Update();
private:
	GameObject* parent_ = nullptr;
	XMFLOAT3 destination_ = { 0.0f, 0.0f, 0.0f }; // –Ú“I’n
	float speed_ = 0.0; // ˆÚ“®‘¬“x

};

