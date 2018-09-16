#pragma once
#include<vector>
class iTile {
public:
	virtual void DetailPrev(int R, int G, int B,int x,int y) = 0;
	virtual void DetailShow(int R, int G, int B) = 0;
};

class Tile {
private:
	int r, g, b;
	int color;
	int x, y;
	iTile *Det;

	int MouseX, MouseY;
public:
	Tile(int RL, int RH, int GL, int GH, int BL, int BH, int inx, int iny,iTile *in);
	void DO();
};

class mTile:public iTile {
private:
	std::vector<Tile*> lT;
	bool DetailFlag;

	int SmallFont;
	int LargeFont;
	int r, g, b;
public:
	mTile();
	void ReMake(int RL, int RH, int GL, int GH, int BL, int BH);
	void DetailPrev(int R, int G, int B, int x, int y) override;
	void DetailShow(int R, int G, int B) override;
	void DO();
};