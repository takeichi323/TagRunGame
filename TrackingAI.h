#include "Engine/GameObject.h"
#include "Vector3.h"

class TrackingAI{
public:
	TrackingAI(GameObject* parent);
	~TrackingAI();

	void SetDestination(const Vector3& destination);
	void Update();
private:
	GameObject* parent_;
	Vector3 destination_; // –Ú“I’n
	float speed_; // ˆÚ“®‘¬“x

};

