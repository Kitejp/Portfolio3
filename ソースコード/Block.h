#ifndef DEF_BLOCK_H // 二重include防止

#define DEF_BLOCK_H

// ブロックの初期位置（x座標）を定数化
#define DRAW_POSITION 140

// 次のブロックの描画位置を定数化
#define NEXT_BLOCK_X 490
#define NEXT_BLOCK_Y 30

// ホールドしているブロックの描画位置を定数化
#define HOLD_BLOCK_X 60
#define HOLD_BLOCK_Y 20

// ブロックの縦・横を定数化
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4

// ステージの縦・横を定数化
#define STAGE_HEIGHT 23
#define STAGE_WIDTH 18

// ブロック一つ分の幅を定数化
#define DRAW_BLOCK_WIDTH 20

static int block[BLOCK_HEIGHT][BLOCK_WIDTH];

static int blocks[BLOCK_HEIGHT * 6][BLOCK_WIDTH * 4] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,2,2,0,0,0,2,0,0,2,0,0,0,2,2,0},
	{0,0,2,0,0,2,2,0,0,2,2,0,0,2,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,3,3,0,0,3,3,0,0,0,3,0,0,3,0,0},
	{0,3,0,0,0,0,3,0,0,3,3,0,0,3,3,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,4,0,4,0,0,4,4,0,0,0,0,0,4,4,0},
	{0,4,4,4,0,0,4,0,0,4,4,4,0,0,4,0},
	{0,0,0,0,0,0,4,4,0,4,0,4,0,4,4,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,5,0,0,0,0,0,0,0,5,0,0,0,5,0,0},
	{0,5,5,0,5,5,5,0,5,5,0,0,5,5,5,0},
	{0,5,0,0,0,5,0,0,0,5,0,0,0,0,0,0},

	{0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0},
	{0,6,0,0,6,6,6,6,0,6,0,0,6,6,6,6},
	{0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0},
	{0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0}
	};

static int stage[STAGE_HEIGHT][STAGE_WIDTH];
static int turn_Block[BLOCK_HEIGHT][BLOCK_WIDTH];
static int next_Block[BLOCK_HEIGHT][BLOCK_WIDTH];
static int hold_Block[BLOCK_HEIGHT][BLOCK_WIDTH];
static int clear_Line_Point[20];

class BLOCK
{
public:
	int score;
	int level;

	int gameOver_Flag;
	int clear_Flag;

	BLOCK();
	~BLOCK();

	void InitBlockVariable(void);
	void MakeBlock(void);
	void DrawBlock(void);
	void DrawStage(void);
	void FallBlock(void);
	void MoveBlock(void);
	void TurnRight(void);
	void TurnLeft(void);
	void SaveBlock(void);
	void FixBlock(void);
	void GameOver(void);
	void DrawVariable(void);
	void ClearLine(void);
	void ResetGame(void);

private:
	// ブロックのx座標
	int block_X;
	// ブロックのy座標(内部計算用)
	int block_Y;
	// ブロックのy座標(表示用)
	float block_Y_Count;
	// ブロックの落ちる速度
	float block_Speed;

	// 色
	int color_Red;
	int color_Black;
	int color_Green;
	int color_Yellow;
	int color_Fuchsia;
	int color_Aqua;
	int color_White;
	int color_Turquoise;

	int collision_Flag;
	int make_Block_Flag;
	int hold_Block_Flag;
	int first_Block_Flag;

	int block_Id;
	int next_Block_Id;
	int hold_Block_Id;

	int clear_Count;
	int fix_Count;

	int turn_Point;
	int hold_Turn_Point;
	int block_Y_Point;

	int seHandle;

	void InitBlockVariable2(void);
	void HoldBlock(void);
	void CollisionLeft(void);
	void CollisionRight(void);
	void CollisionBottom(void);
	void CollisionCenter(void);
	void CollisionTurn(void);
	void SearchLine(void);
	void ChangeLevel(void);
};

#endif // !DEF_BLOCK_H

