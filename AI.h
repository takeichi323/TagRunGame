#pragma once
#include <iostream>

//�I�u�W�F�N�g�̍��W��\���\����
struct Point
{
	float x;
	float y;

};

class AI{
public:


	//�R���X�g���N�^
	AI();

	//���W�擾�֐�
	void GetPosition(Point& player, Point& enemy);
	//�Q��(player,enemy)�̋������v�Z����֐�
	float RangeCalculation(const Point& p1, const Point& p2);

	//���^AI
	void MetaAI();
	//�L�����N�^AI
	void CharacterAI();
	//�i�r�Q�[�V����AI
	void NavigationAI();




};

/*�����������{
���^AI����������N���X
�L�����N�^AI����������N���X
�i�r�Q�[�V��������������N���X
}*/
