#include "Engine/GameObject.h"
#include "Vector3.h"

class TrackingAI{
public:
	TrackingAI(GameObject* parent);
	~TrackingAI();

	void SetDestination(const XMFLOAT3& destination);
	void Update();
private:
	GameObject* parent_;
	XMFLOAT3 destination_; // –Ú“I’n
	float speed_; // ˆÚ“®‘¬“x

};

