#include <iostream>
#include <cmath>
#include "AI.h"
#include "Player.h"
#include "Enemy.h"

AI::AI()
{
}

//�v���C���[�ƓG�̍��W���擾����֐�
void AI::GetPosition(Point& player, Point& enemy)
{
    /*�v���C���[�̈ʒu�ƓG�̈ʒu�������ɂԂ�����
    �@���W�f�[�^���������ϐ����Q�Ƃ�����*/
}

float AI::RangeCalculation(const Point& p1, const Point& p2)
{
    /*2�_�̈ʒu���v�Z���Đ��l��return�ŕԂ�*/
    return 0.0f;
}

void AI::MoveTowards(Point& enemy, const Point& player, float speed)
{
    /*�v���C���[�Ɍ������Ĉړ�����
    �@�v���C���[�̕����ւ̒P�ʃx�N�g�����v�Z
     �@�ړ��ʂ��v�Z���A�G���ړ�������*/
}

void AI::MetaAI()
{
    /*���^AI��邱��
     �L�����N�^�[AI�ƃi�r�Q�[�V����Ai�̒����
     �i�r�Q�[�V����AI��������擾
     ����Ai�Ɏw���o��*/
}

void AI::CharacterAI()
{
}

void AI::NavigationAI()
{
    /*�}�b�v��񁕎�l���̈ʒu�������̈ʒu�擾*/

}
