#include "DxLib.h"
#include "Block.h"
#include "BackGround.h"
#include "KeyBoard.h"

int game_State;

static BLOCK* blockClass;
static BACKGROUND* bgClass;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	// �c�w���C�u����������
	DxLib_Init();
	// �`����ʂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	game_State = 0;
	blockClass = new BLOCK;
	bgClass = new BACKGROUND;

	// �ϐ��̏�����
	blockClass->InitBlockVariable();
	// BGM�̍Đ�
	PlaySound("./stagebgm.mp3", DX_PLAYTYPE_LOOP);

	// ���C�����[�v
	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		bgClass->DrawBackGround();

		switch (game_State) {
		case 0:
			bgClass->DrawTitle();
			KeyBoardUpdate();

			if (KeyBoardGet(KEY_INPUT_RETURN) == 1)
				game_State = 1;

			if (KeyBoardGet(KEY_INPUT_ESCAPE) == 1)
				return 0;

			break;
		case 1:
			blockClass->DrawVariable();
			blockClass->DrawStage();
			bgClass->DrawOperation();

			if (blockClass->clear_Flag == 0) {
				blockClass->MakeBlock();
				blockClass->DrawBlock();
				blockClass->MoveBlock();
				blockClass->FallBlock();
				blockClass->FixBlock();
				blockClass->GameOver();
				KeyBoardUpdate();
			}
			else
				blockClass->ClearLine();

			if (blockClass->gameOver_Flag == 1)
				game_State = 2;

			break;
		case 2:
			bgClass->DrawGameOver();
			KeyBoardUpdate();

			if (KeyBoardGet(KEY_INPUT_RETURN) == 1) {
				blockClass->ResetGame();
				game_State = 0;
			}

			if (KeyBoardGet(KEY_INPUT_ESCAPE) == 1)
				return 0;

			break;
		default:
			break;
		}

		// ��ʂ�؂�ւ���
		ScreenFlip();
	}

	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	delete blockClass;
	delete bgClass;
	return 0; // �\�t�g�̏I�� 
}