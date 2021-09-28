#include "DxLib.h"
#include "BackGround.h"

BACKGROUND::BACKGROUND()
{
	// 背景の設定
	back_img1 = LoadGraph("./back_img1.jpg");
	// 白色の取得
	color_White = GetColor(255, 255, 255);
}

BACKGROUND::~BACKGROUND()
{
}

// 背景の配置を行う関数
void BACKGROUND::DrawBackGround() {
	DrawGraph(0, 0, back_img1, TRUE);
}

// タイトルの文字を表示する関数
void BACKGROUND::DrawTitle() {
	DrawFormatString(230, 220, color_White, "ブロックパズルゲーム");
	DrawFormatString(210, 260, color_White, "ゲームスタート：Enterキー");
	DrawFormatString(210, 300, color_White, "ゲームを終了する：Escキー");
}

// 操作方法を表示する関数
void BACKGROUND::DrawOperation() {
	DrawFormatString(20, 200, color_White, "操作説明");
	DrawFormatString(20, 240, color_White, "左へ移動");
	DrawFormatString(20, 260, color_White, "A or ← キー");
	DrawFormatString(20, 280, color_White, "右へ移動");
	DrawFormatString(20, 300, color_White, "D or → キー");
	DrawFormatString(20, 320, color_White, "落下");
	DrawFormatString(20, 340, color_White, "S or ↓ キー");
	DrawFormatString(20, 360, color_White, "右回転");
	DrawFormatString(20, 380, color_White, "W or ↑ キー");

	DrawFormatString(500, 240, color_White, "左回転");
	DrawFormatString(500, 260, color_White, "Z キー");
	DrawFormatString(500, 280, color_White, "ホールド");
	DrawFormatString(500, 300, color_White, "H キー");
}

// ゲームオーバーの文字を表示する関数
void BACKGROUND::DrawGameOver() {
	DrawFormatString(260, 220, color_White, "ゲームオーバー");
	DrawFormatString(210, 260, color_White, "タイトルに戻る：Enterキー");
	DrawFormatString(210, 300, color_White, "ゲームを終了する：Escキー");
}