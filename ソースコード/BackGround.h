#ifndef DEF_BACKGROUND_H // ìÒèdincludeñhé~

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
	// îwåiÇÃâÊëú
	int back_img1;
	int color_White;
};

#endif // !DEF_BACKGROUND_H

