#ifndef DEF_BACKGROUND_H // ��dinclude�h�~

#define DEF_BACKGROUND_H

class BACKGROUND
{
public:
	BACKGROUND();
	~BACKGROUND();

	void DrawBackGround(void);
	void DrawTitle(void);
	void DrawOperation();
	void DrawGameOver(void);

private:
	// �w�i�̉摜
	int back_img1;
	int color_White;
};

#endif // !DEF_BACKGROUND_H

