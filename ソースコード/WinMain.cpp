#include "DxLib.h"
#include "Block.h"
#include "BackGround.h"
#include "KeyBoard.h"

int game_State;

static BLOCK* blockClass;
static BACKGROUND* bgClass;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	// ＤＸライブラリ初期化
	DxLib_Init();
	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	game_State = 0;
	blockClass = new BLOCK;
	bgClass = new BACKGROUND;

	// 変数の初期化
	blockClass->InitBlockVariable();
	// BGMの再生
	PlaySound("./stagebgm.mp3", DX_PLAYTYPE_LOOP);

	// メインループ
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

		// 画面を切り替える
		ScreenFlip();
	}

	DxLib_End(); // ＤＸライブラリ使用の終了処理
	delete blockClass;
	delete bgClass;
	return 0; // ソフトの終了 
}