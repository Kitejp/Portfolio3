#include "DxLib.h"
#include "Block.h"
#include "KeyBoard.h"
#include <time.h>

BLOCK::BLOCK()
{
	// x軸、y軸の設定
	block_X = 7;
	block_Y = 0;
	block_Y_Count = 0;
	// ブロックが落ちる速度
	block_Speed = 0.5f;

	collision_Flag = 0;
	make_Block_Flag = 1;
	gameOver_Flag = 0;
	clear_Flag = 0;
	hold_Block_Flag = 0;
	first_Block_Flag = 1;

	block_Id = 0;
	next_Block_Id = 0;
	hold_Block_Id = 0;

	clear_Count = 0;
	fix_Count = 0;

	turn_Point = 0;
	hold_Turn_Point = 0;
	block_Y_Point = 0;

	score = 0;
	level = 1;

	seHandle = LoadSoundMem("./clear_se.mp3");

	color_Red = GetColor(255, 0, 0);
	color_Black = GetColor(0, 0, 0);
	color_Green = GetColor(0, 255, 0);
	color_Yellow = GetColor(255, 255, 0);
	color_Fuchsia = GetColor(255, 0, 255);
	color_Aqua = GetColor(0, 255, 255);
	color_White = GetColor(255, 255, 255);
	color_Turquoise = GetColor(64, 224, 208);
}

BLOCK::~BLOCK()
{
}

// 変数の初期化を行う関数
void BLOCK::InitBlockVariable() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			stage[i][0] = 9;
			stage[i][1] = 9;
			stage[i][2] = 9;
			stage[20][j] = 9;
			stage[21][j] = 9;
			stage[22][j] = 9;
			stage[i][15] = 9;
			stage[i][16] = 9;
			stage[i][17] = 9;
		}
	}

	block_X = 7;
	block_Y = 0;
	block_Y_Count = 0;
	block_Speed = 0.5f;

	collision_Flag = 0;
	make_Block_Flag = 1;
	gameOver_Flag = 0;
	clear_Flag = 0;
	hold_Block_Flag = 0;
	first_Block_Flag = 1;

	block_Id = 0;
	next_Block_Id = 0;
	hold_Block_Id = 0;

	clear_Count = 0;
	fix_Count = 0;

	turn_Point = 0;
	hold_Turn_Point = 0;
	block_Y_Point = 0;

	score = 0;
	level = 1;

	srand((unsigned)time(NULL));
}

// 次のブロックを描画する際に変数の初期化を行う関数
void BLOCK::InitBlockVariable2() {
	// x軸、y軸の設定
	block_X = 7;
	block_Y = 0;
	block_Y_Count = 0;
	make_Block_Flag = 1;
	turn_Point = 0;
	block_Y_Point = 0;
	fix_Count = 0;
}

// 確認用
void BLOCK::DrawVariable() {
	DrawBox(470, 10, 610, 160, color_White, FALSE);
	DrawBox(30, 10, 170, 160, color_White, FALSE);

	DrawFormatString(480, 10, color_White, "次のブロック");
	DrawFormatString(40, 10, color_White, "ホールド");

	DrawFormatString(500, 120, color_White, "スコア: %d", score * 10);
	DrawFormatString(500, 140, color_White, "レベル: %d", level);

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (next_Block[y][x] == 1)
				DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, color_Red, "■");
			else if (next_Block[y][x] == 2)
				DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, color_Green, "■");
			else if (next_Block[y][x] == 3)
				DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, color_Turquoise, "■");
			else if (next_Block[y][x] == 4)
				DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, color_Yellow, "■");
			else if (next_Block[y][x] == 5)
				DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, color_Fuchsia, "■");
			else if (next_Block[y][x] == 6)
				DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, color_Aqua, "■"); 
		}
	}

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (hold_Block[y][x] == 1)
				DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, color_Red, "■"); 
			else if (hold_Block[y][x] == 2)
				DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, color_Green, "■");
			else if (hold_Block[y][x] == 3)
				DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, color_Turquoise, "■"); 
			else if (hold_Block[y][x] == 4)
				DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, color_Yellow, "■");
			else if (hold_Block[y][x] == 5)
				DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, color_Fuchsia, "■");
			else if (hold_Block[y][x] == 6) 
				DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, color_Aqua, "■"); 
		}
	}
}

//ブロックを登録する関数
//先に生成したブロックを「next_Block_Id」に保存
//すぐに「block_id」に保存しなおして再び
//ブロック生成処理を行い「next_Block_Id」に保存する
//２回目以降はこれを繰り返す
void BLOCK::MakeBlock() {
	if (first_Block_Flag == 1) {
		next_Block_Id = (rand() % 6);

		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++)
				next_Block[y][x] = blocks[(next_Block_Id * BLOCK_HEIGHT) + y][x];
		}

		first_Block_Flag = 0;
	}


	if (make_Block_Flag == 1) {
		block_Id = next_Block_Id;
		next_Block_Id = (rand() % 6);

		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				block[y][x] = next_Block[y][x];
				next_Block[y][x] = blocks[(next_Block_Id * BLOCK_HEIGHT) + y][x];
			}
		}

		make_Block_Flag = 0;
	}
}

// ブロックを描画する関数
void BLOCK::DrawBlock() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] == 1)
				DrawFormatString(DRAW_POSITION + block_X * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
					block_Y_Count + y * DRAW_BLOCK_WIDTH, color_Red, "■");
			else if (block[y][x] == 2)
				DrawFormatString(DRAW_POSITION + block_X * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
					block_Y_Count + y * DRAW_BLOCK_WIDTH, color_Green, "■");
			else if (block[y][x] == 3)
				DrawFormatString(DRAW_POSITION + block_X * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
					block_Y_Count + y * DRAW_BLOCK_WIDTH, color_Turquoise, "■");
			else if (block[y][x] == 4)
				DrawFormatString(DRAW_POSITION + block_X * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
					block_Y_Count + y * DRAW_BLOCK_WIDTH, color_Yellow, "■");
			else if (block[y][x] == 5)
				DrawFormatString(DRAW_POSITION + block_X * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
					block_Y_Count + y * DRAW_BLOCK_WIDTH, color_Fuchsia, "■");
			else if (block[y][x] == 6)
				DrawFormatString(DRAW_POSITION + block_X * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
					block_Y_Count + y * DRAW_BLOCK_WIDTH, color_Aqua, "■");
		}
	}
}

// ステージを描画する関数
void BLOCK::DrawStage() {
	for (int y = 0; y < STAGE_HEIGHT - 2; y++) {
		for (int x = 2; x < STAGE_WIDTH - 2; x++) {
			if (stage[y][x] == 1)
				DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH, y * DRAW_BLOCK_WIDTH, color_Red, "■");
			else if (stage[y][x] == 2)
				DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH, y * DRAW_BLOCK_WIDTH, color_Green, "■");
			else if (stage[y][x] == 3)
				DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH, y * DRAW_BLOCK_WIDTH, color_Turquoise, "■");
			else if (stage[y][x] == 4)
				DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH, y * DRAW_BLOCK_WIDTH, color_Yellow, "■");
			else if (stage[y][x] == 5)
				DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH, y * DRAW_BLOCK_WIDTH, color_Fuchsia, "■");
			else if (stage[y][x] == 6)
				DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH, y * DRAW_BLOCK_WIDTH, color_Aqua, "■");
			else if (stage[y][x] == 9)
				DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH, y * DRAW_BLOCK_WIDTH, color_Black, "■");
		}
	}
}

/*---当たり判定---*/

// ブロックの左側
void BLOCK::CollisionLeft() {
	collision_Flag = 0;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_Y + y][block_X + (x - 1)] != 0)
					collision_Flag = 1;
				else if ((int)(block_Y_Count - (block_Y * DRAW_BLOCK_WIDTH)) > 0) {
					if (stage[block_Y + (y + 1)][block_X + (x - 1)] != 0)
						collision_Flag = 1;
				}
			}
		}
	}
}

// ブロックの右側
void BLOCK::CollisionRight() {
	collision_Flag = 0;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_Y + y][block_X + (x + 1)] != 0)
					collision_Flag = 1;
				else if ((int)(block_Y_Count - (block_Y * DRAW_BLOCK_WIDTH)) > 0) {
					if (stage[block_Y + (y + 1)][block_X + (x + 1)] != 0)
						collision_Flag = 1;
				}
			}
		}
	}
}

// ブロックの底
void BLOCK::CollisionBottom() {
	collision_Flag = 0;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_Y + (y + 1)][block_X + x] != 0)
					collision_Flag = 1;
			}
		}
	}
}

// ブロックの中心
void BLOCK::CollisionCenter() {
	collision_Flag = 0;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_Y + y][block_X + x] != 0)
					collision_Flag = 1;
			}
		}
	}
}

// ブロックが回転する時
void BLOCK::CollisionTurn() {
	collision_Flag = 0;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (turn_Block[y][x] != 0) {
				if (stage[block_Y + y][block_X + x] != 0)
					collision_Flag = 1;
			}
		}
	}
}

/*---ここまで当たり判定---*/

// ブロックを落下させる関数
void BLOCK::FallBlock() {
	if (make_Block_Flag == 0) {
		block_Y_Count += block_Speed;
		block_Y = block_Y_Count / DRAW_BLOCK_WIDTH;
	}
}

//ブロックホールド処理
//初回ホールド時はそのまま「hold_Block[4][4]」に
//その時の「block_Id」など共に保存、初期化の「InitBlockVariable2()」を行う
//２回目以降は先ほどの「hold_Block[4][4]」との入れ替え処理を行い
//そのままブロックの位置だけを元に戻す
void BLOCK::HoldBlock() {
	int tmp_Block[4][4] = { 0 };
	int tmp_Block_Id;
	int tmp_Turn_Point;

	if (hold_Block_Flag == 0) {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++)
				hold_Block[y][x] = block[y][x];
		}

		hold_Block_Id = block_Id;
		hold_Turn_Point = turn_Point;
		InitBlockVariable2();
		MakeBlock();
		hold_Block_Flag = 1;
	}
	else {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				tmp_Block[y][x] = block[y][x];
				block[y][x] = hold_Block[y][x];
				hold_Block[y][x] = tmp_Block[y][x];
			}
		}

		tmp_Block_Id = block_Id;
		tmp_Turn_Point = turn_Point;
		block_Id = hold_Block_Id;
		turn_Point = hold_Turn_Point;
		hold_Block_Id = tmp_Block_Id;
		hold_Turn_Point = tmp_Turn_Point;

		block_X = 7;
		block_Y = 0;
		block_Y_Count = 0;
	}
}

// ブロックを操作する関数
void BLOCK::MoveBlock() {
	if (KeyBoardGet(KEY_INPUT_A) % 5 == 1 || KeyBoardGet(KEY_INPUT_LEFT) % 5 == 1) {
		CollisionLeft();

		if (collision_Flag == 0)
			block_X--;
	}

	if (KeyBoardGet(KEY_INPUT_D) % 5 == 1 || KeyBoardGet(KEY_INPUT_RIGHT) % 5 == 1) {
		CollisionRight();

		if (collision_Flag == 0)
			block_X++;
	}

	if (KeyBoardGet(KEY_INPUT_S) % 5 == 1 || KeyBoardGet(KEY_INPUT_DOWN) % 5 == 1) {
		CollisionBottom();

		if (collision_Flag == 0) {
			block_Y++;
			block_Y_Count = block_Y * DRAW_BLOCK_WIDTH;
		}
	}

	if (KeyBoardGet(KEY_INPUT_W) == 1 || KeyBoardGet(KEY_INPUT_UP) == 1)
		TurnRight();

	if (KeyBoardGet(KEY_INPUT_Z) == 1)
		TurnLeft();

	if (KeyBoardGet(KEY_INPUT_H) == 1)
		HoldBlock();
}

// ブロックを右回転する関数
void BLOCK::TurnRight() {
	turn_Point++;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++)
			turn_Block[y][x] = blocks[(block_Id * BLOCK_HEIGHT) + y][(turn_Point % 4 * BLOCK_WIDTH) + x];
	}

	CollisionTurn();

	if (collision_Flag == 0) {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++)
				block[y][x] = turn_Block[y][x];
		}
	}
	else 
		turn_Point--;
}

// ブロックを左回転する関数
void BLOCK::TurnLeft() {
	turn_Point += 3;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++)
			turn_Block[y][x] = blocks[(block_Id * BLOCK_HEIGHT) + y][(turn_Point % 4 * BLOCK_WIDTH) + x];
	}

	CollisionTurn();

	if (collision_Flag == 0) {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++)
				block[y][x] = turn_Block[y][x];
		}
	}
	else
		turn_Point -= 3;
}

// 落下したブロックをステージの配列に入れる関数
void BLOCK::SaveBlock() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++)
			stage[block_Y + y][block_X + x] += block[y][x];
	}
}

void BLOCK::FixBlock() {
	CollisionBottom();

	if (collision_Flag != 0) {
		if (block_Y_Point == block_Y && fix_Count > 10) {
			SaveBlock();
			SearchLine();

			if (clear_Flag == 0)
				InitBlockVariable2();
		}
		else {
			if (block_Y_Point == block_Y)
				fix_Count++;
			else
				fix_Count = 0;

			block_Y_Point = block_Y;
			block_Y_Count -= block_Speed;
		}
	}
}

// ゲームオーバーのフラグを起こす関数
void BLOCK::GameOver() {
	CollisionCenter();

	if (collision_Flag != 0) {
		if (clear_Flag == 0)
			gameOver_Flag = 1;
	}
}

// 
void BLOCK::SearchLine() {
	for (int i = 0; i < STAGE_HEIGHT - 3; i++)
		clear_Line_Point[i] = 0;

	for (int i = 0; i < STAGE_HEIGHT - 3; i++) {
		for (int j = 3; j < STAGE_WIDTH - 3; j++) {
			if (stage[i][j] == 0) {
				clear_Line_Point[i] = 1;
				break;
			}
		}
	}

	for (int i = 0; i < STAGE_HEIGHT - 3; i++) {
		if (clear_Line_Point[i] == 0) {
			clear_Flag = 1;
			score++;
			PlaySoundMem(seHandle, DX_PLAYTYPE_BACK);
		}
	}
}

void BLOCK::ClearLine() {
	int remain_Line_Point[20] = { 0 };
	int remain_Line_Index = 0;

	if (clear_Count < 12) {
		for (int i = 0; i < STAGE_HEIGHT - 3; i++) {
			if (clear_Line_Point[i] == 0) {
				stage[i][clear_Count + 3] = 0;
			}
		}
		clear_Count++;
	}
	else {
		// クリアした場所の入れ替え処理
		for (int i = STAGE_HEIGHT - 4; i >= 0; i--) {
			if (clear_Line_Point[i] != 0) {
				remain_Line_Point[remain_Line_Index] = i;
				remain_Line_Index++;
			}
		}

		remain_Line_Index = 0;
		for (int i = STAGE_HEIGHT - 4; i >= 0; i--) {
			for (int j = 3; j < STAGE_HEIGHT - 3; j++) {
				stage[i][j] = stage[remain_Line_Point[remain_Line_Index]][j];
			}
			remain_Line_Index++;
		}

		clear_Flag = 0;
		clear_Count = 0;
		InitBlockVariable2();
		ChangeLevel();
	}
}

// スコアによってブロックが落ちる速度を速くしていく関数
void BLOCK::ChangeLevel() {
	if (score < 10) {
		level = 1;
		block_Speed = 0.5f;
	}
	else if (score < 20) {
		level = 2;
		block_Speed = 1;
	}
	else if (score < 30) {
		level = 3;
		block_Speed = 2;
	}
	else if (score < 40) {
		level = 4;
		block_Speed = 4;
	}
	else {
		level = 5;
		block_Speed = 8;
	}
}

void BLOCK::ResetGame() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++)
			stage[i][j] = 0;
	}

	InitBlockVariable();
}