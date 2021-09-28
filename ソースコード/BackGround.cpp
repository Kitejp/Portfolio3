#include "DxLib.h"
#include "BackGround.h"

BACKGROUND::BACKGROUND()
{
	// �w�i�̐ݒ�
	back_img1 = LoadGraph("./back_img1.jpg");
	// ���F�̎擾
	color_White = GetColor(255, 255, 255);
}

BACKGROUND::~BACKGROUND()
{
}

// �w�i�̔z�u���s���֐�
void BACKGROUND::DrawBackGround() {
	DrawGraph(0, 0, back_img1, TRUE);
}

// �^�C�g���̕�����\������֐�
void BACKGROUND::DrawTitle() {
	DrawFormatString(230, 220, color_White, "�u���b�N�p�Y���Q�[��");
	DrawFormatString(210, 260, color_White, "�Q�[���X�^�[�g�FEnter�L�[");
	DrawFormatString(210, 300, color_White, "�Q�[�����I������FEsc�L�[");
}

// ������@��\������֐�
void BACKGROUND::DrawOperation() {
	DrawFormatString(20, 200, color_White, "�������");
	DrawFormatString(20, 240, color_White, "���ֈړ�");
	DrawFormatString(20, 260, color_White, "A or �� �L�[");
	DrawFormatString(20, 280, color_White, "�E�ֈړ�");
	DrawFormatString(20, 300, color_White, "D or �� �L�[");
	DrawFormatString(20, 320, color_White, "����");
	DrawFormatString(20, 340, color_White, "S or �� �L�[");
	DrawFormatString(20, 360, color_White, "�E��]");
	DrawFormatString(20, 380, color_White, "W or �� �L�[");

	DrawFormatString(500, 240, color_White, "����]");
	DrawFormatString(500, 260, color_White, "Z �L�[");
	DrawFormatString(500, 280, color_White, "�z�[���h");
	DrawFormatString(500, 300, color_White, "H �L�[");
}

// �Q�[���I�[�o�[�̕�����\������֐�
void BACKGROUND::DrawGameOver() {
	DrawFormatString(260, 220, color_White, "�Q�[���I�[�o�[");
	DrawFormatString(210, 260, color_White, "�^�C�g���ɖ߂�FEnter�L�[");
	DrawFormatString(210, 300, color_White, "�Q�[�����I������FEsc�L�[");
}